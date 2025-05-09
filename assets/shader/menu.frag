uniform float time;
uniform vec2 resolution;

const vec2 HASH_VECTOR = vec2(127.1, 311.7);
const float HASH_SCALE = 43758.5453123;
const float GAMMA = 0.45;

float hash(vec2 p) { return fract(sin(dot(p, HASH_VECTOR)) * HASH_SCALE); }

float noise(vec2 p) {
    vec2 i = floor(p);
    vec2 f = fract(p);
    float a = hash(i);
    float b = hash(i + vec2(1.0, 0.0));
    float c = hash(i + vec2(0.0, 1.0));
    float d = hash(i + vec2(1.0, 1.0));
    vec2 u = f * f * (3.0 - 2.0 * f);
    return mix(a, b, u.x) + (c - a) * u.y * (1.0 - u.x) + (d - b) * u.x * u.y;
}

void main() {
    vec2 uv = gl_FragCoord.xy / resolution.xy;

    float flowX = sin(uv.y * 10.0 + time * 0.5);
    float flowY = cos(uv.x * 10.0 + time * 0.3);
    vec2 flow = vec2(flowX, flowY);
    uv += 0.04 * flow;

    float n1 = noise(uv * 10.0 + time * 0.1);
    float n2 = noise(uv * 20.0 - time * 0.15);
    float n3 = noise(uv * 40.0 + time * 0.2);

    float grain = (n1 * 0.5 + n2 * 0.3 + n3 * 0.2);

    vec3 sandLight = vec3(0.95, 0.85, 0.65);
    vec3 sandDark = vec3(0.75, 0.6, 0.4);

    vec3 color = mix(sandDark, sandLight, grain);
    color = pow(color, vec3(1.0 / GAMMA));

    gl_FragColor = vec4(color, 1.0);
}
