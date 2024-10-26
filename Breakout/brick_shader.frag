uniform float time;

void main()
{
    gl_FragColor = vec4(sin(90 + time + (gl_FragCoord.x + 700) / 150), sin(0 + time + (gl_FragCoord.x + 700) / 150), sin(180 + time + (gl_FragCoord.x + 700) / 150), 1.0);
}