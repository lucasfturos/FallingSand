uniform sampler2D texture;
uniform vec2 resolution;
uniform float time;

const float CURVATURE = 5.0;
const float BLUR = 0.021;
const float CA_AMT = 1.024;

float rand(vec2 co) {
    return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

float randInRange(vec2 range, vec2 seed) {
    float r = (rand(seed) + 1.0) / 2.0;
    return range.x + r * (range.y - range.x);
}

void main() {
    vec2 uv = gl_FragCoord.xy / resolution;

    // FLICKER
    float flickerPeriod = randInRange(vec2(1.5, 3.0), vec2(time, time));
    float noiseScale = 0.01;
    if (fract(time / flickerPeriod) > 0.95) {
        noiseScale = 0.2;
    }

    vec2 flickerSeed = vec2(time, uv.y);
    uv.x += randInRange(vec2(-0.01, 0.01), flickerSeed);

    // CURVATURE
    vec2 crtUV = uv * 2.0 - 1.0;
    vec2 offset = crtUV.yx / CURVATURE;
    crtUV += crtUV * offset * offset;
    crtUV = crtUV * 0.5 + 0.5;

    // EDGE BLUR
    vec2 edge = smoothstep(0.0, BLUR, crtUV) *
                (1.0 - smoothstep(1.0 - BLUR, 1.0, crtUV));

    // CHROMATIC ABERRATION
    float r = texture2D(texture, (crtUV - 0.5) * CA_AMT + 0.5).r;
    float g = texture2D(texture, crtUV).g;
    float b = texture2D(texture, (crtUV - 0.5) / CA_AMT + 0.5).b;
    vec3 color = vec3(r, g, b) * edge.x * edge.y;

    // SCANLINES
    if (mod(gl_FragCoord.y, 2.0) < 1.0)
        color *= 0.7;
    else if (mod(gl_FragCoord.x, 3.0) < 1.0)
        color *= 0.7;
    else
        color *= 1.2;

    float noise = randInRange(vec2(0.0, noiseScale), flickerSeed);
    color += vec3(noise);

    gl_FragColor = vec4(color, 1.0);
}
