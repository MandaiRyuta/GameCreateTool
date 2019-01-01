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
    float height : packoffset(c0);
    float frequency : packoffset(c1);
}

struct VS_IN
{
    float3 position : POSITION;
};

struct PS_IN
{
    float4 sv_position : SV_Position;
    float4 position : TEXCOORD0;
};

struct PS_OUT
{
    float4 color : SV_Target0;
};

PS_IN VS(VS_IN input)
{
    PS_IN output = (PS_IN) 0;
    
    matrix wvp = mul(world_, mul(view_, projection_));

    float noise = rand(float3(input.position.x * frequency, input.position.z * frequency, 0.5f));

    input.position.y = noise * height;
    
    output.sv_position = mul(float4(input.position,1.0f), wvp);

    output.position = mul(float4(input.position, 1), world_);

    return output;
}

PS_OUT PS(PS_IN input)
{
    PS_OUT output = (PS_OUT) 0;

    output.color = input.position;

    return output;
}