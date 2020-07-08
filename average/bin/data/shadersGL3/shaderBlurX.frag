#version 150

uniform sampler2DRect tex0;
uniform float blurAmnt;

in vec2 texCoordVarying;
out vec4 outputColor;

// Gaussian weights from http://dev.theomader.com/gaussian-kernel-calculator/

void main()
{

    vec4 color = vec4(0.0, 0.0, 0.0, 255.0);

    float acc = 0;

    if (texture(tex0, texCoordVarying + vec2(-4.0, 0.0) ).r  > 0.5) {
        acc = acc + 1;
    }
    if (texture(tex0, texCoordVarying + vec2(-3.0, 0.0) ).r  > 0.5) acc++;
    if (texture(tex0, texCoordVarying + vec2(-2.0, 0.0) ).r  > 0.5) acc++;
    if (texture(tex0, texCoordVarying + vec2(-1.0, 0.0) ).r  > 0.5) acc++;
    if (texture(tex0, texCoordVarying + vec2(+4.0, 0.0) ).r  > 0.5) acc++;
    if (texture(tex0, texCoordVarying + vec2(+3.0, 0.0) ).r  > 0.5) acc++;
    if (texture(tex0, texCoordVarying + vec2(+2.0, 0.0) ).r  > 0.5) acc++;
    if (texture(tex0, texCoordVarying + vec2(+1.0, 0.0) ).r  > 0.5) acc++;


    

    if ( acc > 7 ) {
        color = vec4( 1.0, 1.0, 1.0, 1.0 );
    }
    else if ( acc > 0 ) {
        color = vec4( 0, 0.0, 0.0, 1.0 );
    }
    else {
        color = vec4( 0.0, 0.0, 0.0, 1.0 );
    }

    // color = texture(tex0, texCoordVarying + vec2( 0.0, 0.0 ) ) * 0.5;
    outputColor = color;
}
