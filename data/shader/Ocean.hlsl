#ifndef OCEAN_HS_PARTITION
#define OCEAN_HS_PARTITION "fractional_even"
#endif

#define INPUT_PATCH_SIZE 4
#define OUTPUT_PATCH_SIZE 4

cbuffer PerCamera : register(b0)
{
    row_major matrix view_ : packoffset(c0);
    row_major matrix projection_ : packoffset(c4);
    float4 color : packoffset(c8);
    float2 view_port : packoffset(c9);
    float3 eye_position_ : packoffset(c10);
};

cbuffer PerMesh : register(b1)
{
    row_major matrix world_ : packoffset(c0);
    float4 diffuse_ : packoffset(c4);
};

cbuffer unique : register(b2)
{
    float time : packoffset(c0);
    float minDistance : packoffset(c1);
    float maxDistance : packoffset(c2);
    float minTessExp : packoffset(c3);
    float maxTessExp : packoffset(c4);
    float sizeTerrain : packoffset(c5);
    bool applyCorrection : packoffset(c6);
};

Texture2D bumpTexture : register(t0);

TextureCube envMap : register(t1);

SamplerState linearSampler;

struct DS_OUTPUT
{
    float4 vPosition : SV_POSITION;
    float3 vWorldPos : WORLDPOS;
    float3 vNormal : NORMAL;
    float3 vBinormal : BINORMAL;
    float3 vTangent : TANGENT;
};

struct VERTEX_POSITION
{
    float3 vPosition : POSITION;
};

struct HS_CONSTANT_DATA_OUTPUT
{
    float Edges[4] : SV_TessFactor;
    float Inside[2] : SV_InsideTessFactor;
};

//wave record
struct Wave
{
    float wavelength;
    float amplitude;
    float3 direction;
};

//wave data
#define NWAVES 8
static const Wave wave[NWAVES] =
{
    { 65.0f, 1.0f, float3(0.98, 0, 0.17) },
    { 43.5f, 0.6f, float3(0.98, 0, -0.17) },
    { 22.0f, 0.4f, float3(0.934, 0, 0.342) },
    { 99.0f, 2.0f, float3(0.934, 0, -0.342) },
    { 25.0f, 0.3f, float3(0.97, 0, 0.24) },
    { 47.5f, 0.5f, float3(0.97, 0, -0.24) },
    { 57.0f, 0.9f, float3(0.99, 0, -0.14) },
    { 81.0f, 1.6f, float3(0.99, 0, 0.14) }
};

VERTEX_POSITION VS(VERTEX_POSITION Input)
{
    VERTEX_POSITION Output;

    Output.vPosition = Input.vPosition;

    return Output;
}


// This constant hull shader is executed once per patch. It
// will be executed SQRT_NUMBER_OF_PATCHS *
// SQRT_NUMBER_OF_PATCHS times. We calculate a variable
// tessellation factor based on the angle and the distnace
// of the camera.

HS_CONSTANT_DATA_OUTPUT OceanConstantHS(InputPatch<VERTEX_POSITION, INPUT_PATCH_SIZE> ip, uint PatchID : SV_PrimitiveID)
{
    HS_CONSTANT_DATA_OUTPUT Output;

	//Calculating the central point of the patch and the central
	//point for every edge
    float3 middlePoint = (ip[0].vPosition + ip[1].vPosition + ip[2].vPosition + ip[3].vPosition) / 4;
    float3 middlePointEdge0 = (ip[0].vPosition + ip[1].vPosition) / 2;
    float3 middlePointEdge1 = (ip[3].vPosition + ip[0].vPosition) / 2;
    float3 middlePointEdge2 = (ip[2].vPosition + ip[3].vPosition) / 2;
    float3 middlePointEdge3 = (ip[1].vPosition + ip[2].vPosition) / 2;

	//Calculating a correction that will be applied to
	//tessellation factor depending on the angle of the camera
	//We calculate a correction for every central point of the
	//edges and the middle to avoid some lines between patches.
    float2 correctionInside = float2(1, 1);
    float4 correctionEdges = float4(1, 1, 1, 1);

    if (applyCorrection)
    {
        float3 insideDirection0 = normalize(middlePointEdge0 - middlePointEdge2);
        float3 insideDirection1 = normalize(middlePointEdge1 - middlePointEdge3);
        float3 edgeDirection0 = normalize(ip[0].vPosition - ip[1].vPosition);
        float3 edgeDirection1 = normalize(ip[3].vPosition - ip[0].vPosition);
        float3 edgeDirection2 = normalize(ip[2].vPosition - ip[3].vPosition);
        float3 edgeDirection3 = normalize(ip[1].vPosition - ip[2].vPosition);

        float3 toCameraMiddle = normalize(eye_position_ - middlePoint);
        float3 toCameraEdge0 = normalize(eye_position_ - middlePointEdge0);
        float3 toCameraEdge1 = normalize(eye_position_ - middlePointEdge1);
        float3 toCameraEdge2 = normalize(eye_position_ - middlePointEdge2);
        float3 toCameraEdge3 = normalize(eye_position_ - middlePointEdge3);

		//Rank is used to decide how important is the angle correction in front of the distance
        float rank = 0.4;
        float shift = 1 - rank / 2;
        correctionInside.x = ((1.57 - acos(abs(dot(toCameraMiddle, insideDirection0)))) / 1.57) * rank + shift;
        correctionInside.y = ((1.57 - acos(abs(dot(toCameraMiddle, insideDirection1)))) / 1.57) * rank + shift;

        correctionEdges.x = ((1.57 - acos(abs(dot(toCameraEdge0, edgeDirection0)))) / 1.57) * rank + shift;
        correctionEdges.y = ((1.57 - acos(abs(dot(toCameraEdge1, edgeDirection1)))) / 1.57) * rank + shift;
        correctionEdges.z = ((1.57 - acos(abs(dot(toCameraEdge2, edgeDirection2)))) / 1.57) * rank + shift;
        correctionEdges.w = ((1.57 - acos(abs(dot(toCameraEdge3, edgeDirection3)))) / 1.57) * rank + shift;
    }

	//Calculating the distance from the central point of the
	//patch to the camera and from every central point of every
	//edge to the camera
    float magnitude = clamp(distance(middlePoint, eye_position_), minDistance, maxDistance);
    float4 magnitudeEdges;
    magnitudeEdges.x = clamp(distance(middlePointEdge0, eye_position_), minDistance, maxDistance);
    magnitudeEdges.y = clamp(distance(middlePointEdge1, eye_position_), minDistance, maxDistance);
    magnitudeEdges.z = clamp(distance(middlePointEdge2, eye_position_), minDistance, maxDistance);
    magnitudeEdges.w = clamp(distance(middlePointEdge3, eye_position_), minDistance, maxDistance);

	//Calculating the diference between the maximum and the
	//minimum distance
    float diffDistance = maxDistance - minDistance;

	//Calculating a tessellation factor from 0 to 1 for every
	//edge and the middle.
	//We apply the correction depending on the angle of the
	//camera.
    float2 factorInside = 1 - saturate(((magnitude - minDistance) / diffDistance) * correctionInside);
    float4 factorEdges = 1 - saturate(((magnitudeEdges - minDistance) / diffDistance) * correctionEdges);

	//Linear interpolation between the minimum and the maximum
	//tessellation exponent. Then we raised 2
	//to this value to get the tessellation factor.
    Output.Edges[0] = pow(2, lerp(minTessExp, maxTessExp, factorEdges.x));
    Output.Edges[1] = pow(2, lerp(minTessExp, maxTessExp, factorEdges.y));
    Output.Edges[2] = pow(2, lerp(minTessExp, maxTessExp, factorEdges.z));
    Output.Edges[3] = pow(2, lerp(minTessExp, maxTessExp, factorEdges.w));

    Output.Inside[0] = pow(2, lerp(minTessExp, maxTessExp, factorInside.x));
    Output.Inside[1] = pow(2, lerp(minTessExp, maxTessExp, factorInside.y));

    return Output;
}

// The hull shader is called once per output control point,
// which is specified with outputcontrolpoints. In this case,
// we take the control points from the vertex shader and pass
// them directly off to the domain shader.
// The input to the hull shader comes from the vertex shader.
// The output from the hull shader will go to the domain
// shader.
// The tessellation factor, topology, and partition mode will
// go to the fixed function tessellator stage to calculate the
// UVW and domain points.

[domain("quad")]
[partitioning(OCEAN_HS_PARTITION)]
[outputtopology("triangle_cw")]
[outputcontrolpoints(OUTPUT_PATCH_SIZE)]
[patchconstantfunc("OceanConstantHS")]
VERTEX_POSITION HS(InputPatch<VERTEX_POSITION, INPUT_PATCH_SIZE> p, uint i : SV_OutputControlPointID, uint PatchID : SV_PrimitiveID)
{
    VERTEX_POSITION Output;
    Output.vPosition = p[i].vPosition;
    return Output;
}

[domain("quad")]
DS_OUTPUT DS(HS_CONSTANT_DATA_OUTPUT input, float2 UV : SV_DomainLocation, const OutputPatch<VERTEX_POSITION, OUTPUT_PATCH_SIZE> patch)
{
	//Linear interpolation between the position of the corners
    float WorldPosX = lerp(patch[0].vPosition.x, patch[2].vPosition.x, UV.x);
    float WorldPosZ = lerp(patch[0].vPosition.z, patch[2].vPosition.z, UV.y);
	
	//Calculating the position and normal of every vertex
	//depending on the waves
    float3 du = float3(1, 0, 0);
    float3 dv = float3(0, 0, 1);
    float3 displacement = 0;

    matrix vp = mul(view_ , projection_);
	//For every wave
    for (int i = 0; i < NWAVES; i++)
    {
        float pdotk = dot(float3(WorldPosX, 0, WorldPosZ), wave[i].direction);
        float vel = sqrt(1.5621f * wave[i].wavelength);
        float phase = 6.28f / wave[i].wavelength * (pdotk + vel * time);

        float2 offset;
        sincos(phase, offset.x, offset.y);
        offset.x *= -wave[i].amplitude;
        offset.y *= -wave[i].amplitude;

		//We acumulate the displacement of every wave
        displacement += float3(wave[i].direction.x * offset.x, -offset.y, wave[i].direction.z * offset.x);

        float3 da = float3(wave[i].direction.x * offset.y, offset.x, wave[i].direction.z * offset.y);
        da *= 6.28 / wave[i].wavelength;
        du += da * wave[i].direction.x;
        dv += da * wave[i].direction.z;

    }
	
	//Calculation of the final position
    float3 position = float3(WorldPosX, 0, WorldPosZ) + displacement;

    DS_OUTPUT Output;

    Output.vPosition = mul(float4(position, 1), vp);
    Output.vWorldPos = position;
    Output.vBinormal = normalize(du);
    Output.vTangent = normalize(dv);
    Output.vNormal = normalize(cross(dv, du));

    return Output;
}

float4 PS(DS_OUTPUT input) : SV_TARGET
{
    float3 positionWorld = input.vWorldPos;
    float2 coord = float2(positionWorld.x, positionWorld.z) / sizeTerrain;

	//We add some noise to get a more realistic water
    float4 t0 = bumpTexture.Sample(linearSampler, float2(coord * 100 * 0.02 + 2 * 0.07 * float2(1, 0) * (time / 10) * float2(-1, -1)));
    float4 t1 = bumpTexture.Sample(linearSampler, float2(coord * 100 * 0.03 + 2 * 0.057 * float2(0.86, 0.5) * (time / 10) * float2(1, -1)));
    float4 t2 = bumpTexture.Sample(linearSampler, float2(coord * 100 * 0.05 + 2 * 0.047 * float2(0.86, -0.5) * (time / 10) * float2(-1, 1)));
    float4 t3 = bumpTexture.Sample(linearSampler, float2(coord * 100 * 0.07 + 2 * 0.037 * float2(0.7, 0.7) * (time / 10)));

    float3 N = (t0 + t1 + t2 + t3).xzy * 2.0 - 3.3;
    N.xz *= 2.0;

    N = normalize(N);

    float3x3 m;
    m[0] = input.vTangent;
    m[1] = input.vNormal;
    m[2] = input.vBinormal;

    float3 normalWorld = mul(N, m);
    normalWorld = normalize(normalWorld);
	//normalWorld = input.vNormal; //remove bumps

    float3 toCamera = normalize(eye_position_ - positionWorld);

    float cosAngle = max(dot(toCamera, normalWorld), 0);
    float F = 0.02 + 0.98 * pow((1 - cosAngle), 5);

    float4 shallowColor = float4(0.56, 0.62, 0.8, 0);
    float4 deepColor = float4(0.2, 0.3, 0.5, 0);

    float3 reflDir = reflect(eye_position_ - positionWorld, N);
    float4 envColor = envMap.Sample(linearSampler, -reflDir);

    float4 waterColor = deepColor * cosAngle + shallowColor * (1 - cosAngle);

    float4 color = envColor * F + waterColor * (1 - F);

    return color;
}