#version 150

in vec2 texCoordVarying;
out vec4 outputColor;

uniform sampler2DRect colorTex;
uniform sampler2DRect imageMask;


// Gaussian weights from http://dev.theomader.com/gaussian-kernel-calculator/

void main() {

    vec4 color = vec4( 0.0, 0.0, 0.0, 1.0 );

    if (texture(imageMask, texCoordVarying).r  == 1.0) {
        color = texture( colorTex, texCoordVarying );
    }

    outputColor = color;
}
