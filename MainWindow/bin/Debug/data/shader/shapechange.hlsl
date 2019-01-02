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
    
    output.sv_position = mul(float4(input.position, 1.0f), wvp);

    output.position = mul(float4(input.position, 1), world_);

    return output;
}

PS_OUT PS(PS_IN input)
{
    PS_OUT output = (PS_OUT) 0;

    output.color = input.position;

    return output;
}