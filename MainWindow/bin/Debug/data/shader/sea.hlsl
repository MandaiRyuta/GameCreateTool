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
    float2 kpos01 : packoffset(c0); //îgÇÃï˚å¸01
    float2 kpos02 : packoffset(c1); //îgÇÃï˚å¸02
    float2 wlen : packoffset(c2); //îgÇÃí∑Ç≥
    float2 amp : packoffset(c3); //îgÇÃëÂÇ´Ç≥ÅEçÇÇ≥
    float freq : packoffset(c4); //îgÇÃé¸ä˙
    float time : packoffset(c5);
};

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
    float2 k, w;
    k.x = 2.0f * 3.141592f / wlen.x;
    k.y = 2.0f * 3.141592f / wlen.y;
    w.x = 2.0f * 3.141592f / freq;
    w.y = 2.0f * 3.141592f / freq * 2.0f;

    matrix wvp = mul(world_, mul(view_, projection_));
    
    input.position.x = input.position.x - (kpos01.x * k.x * amp.x * (sin(kpos01.x * input.position.x + kpos01.y * input.position.z) - w.x * time) +
                            kpos02.x / k.y * amp.y * sin((kpos02.x * input.position.x + kpos02.y * input.position.z) - w.y * time));

    //input.position.y = amp.x * cos((kpos01.x * input.position.x + kpos01.y * input.position.z) - w.x * time) +
    //                   amp.y * cos((kpos02.x * input.position.x + kpos02.y * input.position.z) - w.y * time);

    input.position.z = input.position.z - (kpos01.y * k.x * amp.x * (sin(kpos01.x * input.position.x + kpos01.y * input.position.z) - w.x * time) +
                            kpos02.y / k.y * amp.y * sin((kpos02.x * input.position.x + kpos02.y * input.position.z) - w.y * time));

    output.sv_position = mul(float4(input.position, 1.0f), wvp);

    output.position = mul(float4(input.position, 1), world_);

    return output;
}

PS_OUT PS(PS_IN input)
{
    PS_OUT output = (PS_OUT) 0;

    output.color = float4(0.2f, 0.8f, 0.6f, 1.f);

    return output;
}