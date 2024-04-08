attribute vec4 a_position;
attribute vec2 a_texCoord;

varying vec2 cc_FragTexCoord1;

float getWind(vec2 vertex, vec2 uv, float timer)
{
    
    float speed = 1.0;
    float minStrength = 0.1;
    float maxStrength = 0.4;
    float strengthScale = 20.0;
    float interval = 3.5;
    float detail = 4.0;
    
    float time = timer * speed + vertex.x * vertex.y;
    float diff = pow(maxStrength - minStrength, 2.0);
    float strength = clamp(minStrength + diff + sin(time / interval) * diff, minStrength, maxStrength) * strengthScale;
    float wind = (sin(time) + cos(time * detail)) * strength * (1.0 - uv.y);
    return wind;
}

void main()
{
    gl_Position = CC_PMatrix * a_position;
    gl_Position.x += getWind(a_position.xy, a_texCoord, CC_Time[1]);
    cc_FragTexCoord1 = a_texCoord;
}
