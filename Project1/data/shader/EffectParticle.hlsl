float hash(float n)
{
    return frac(sin(n) * 43758.5453);
}

float rand(float3 x)
{
    // The noise function returns a value in the range -1.0f -> 1.0f

    float3 p = floor(x);
    float3 f = frac(x);

    f = f * f * f * (3.0 - 2.0 * f);
    float n = p.x + p.y * 57.0 + 113.0 * p.z;

    return lerp(lerp(lerp(hash(n + 0.0), hash(n + 1.0), f.x),
                   lerp(hash(n + 57.0), hash(n + 58.0), f.x), f.y),
               lerp(lerp(hash(n + 113.0), hash(n + 114.0), f.x),
                   lerp(hash(n + 170.0), hash(n + 171.0), f.x), f.y), f.z);
}

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
    row_major matrix InstancingWorld[500] : packoffset(c0);
    float time : packoffset(c2000);
}

struct VS_IN
{
	float3 pos : POSITION;
    float2 texel : TEXCOORD0;
	uint InstanceID : SV_InstanceID;
};

struct VS_OUT
{
	float4 sv_pos : SV_POSITION;
	float2 texel : TEXCOORD0;
};

Texture2D g_DecalMap : register(t0);

SamplerState g_Sampler : register(s0);

VS_OUT VS(VS_IN In)
{
	VS_OUT Out;

    float angle = rand(3.141592f / 20) + 3.141592f * time;
    float angle2 = angle - 3.141592f / 2.0f * 0.8f + 3.141592f * 0.8f / 7 * time + rand(3.141592 / 180.0f);
    float3 move = float3(sin(In.InstanceID) * angle, cos(In.InstanceID) * angle, time + 1.41421356f);
    float3 rse = float3(rand(float3(sin(In.InstanceID), cos(In.InstanceID), tan(move.x / move.y))), rand(float3(sin(In.InstanceID), cos(In.InstanceID), tan(move.x / move.y))), rand(float3(sin(In.InstanceID), cos(In.InstanceID), tan(move.x / move.y))));
    matrix wvp = mul(InstancingWorld[In.InstanceID], mul(view_, projection_));
    Out.sv_pos = mul(float4(In.pos + (In.InstanceID * (move * rse)), 1.0f), wvp);

    Out.texel = In.texel;
	return Out;
}

float4 PS(VS_OUT In) : SV_TARGET
{
    float4 color = g_DecalMap.Sample(g_Sampler, In.texel);

    color.r += 0.5;


    return color;
}