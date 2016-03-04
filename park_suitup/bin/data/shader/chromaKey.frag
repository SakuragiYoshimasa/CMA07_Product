#version 120

uniform sampler2DRect tex0;     // ソースのテクスチャ
uniform float difference;       // 閾値
uniform vec3 chromaKeyColor;    // キーの色
varying vec2 texCoordVarying;

void main()
{
    vec4 texel0 = texture2DRect(tex0, texCoordVarying);
    float diff = length(chromaKeyColor - texel0.rgb);
    if(diff < difference){
        discard;
    }else{
        gl_FragColor = texel0;
    }
}
