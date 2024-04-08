varying vec2 cc_FragTexCoord1;

void main()
{
    // Read the sprite's texture's color for the current pixel.
    vec4 textureColor = texture2D(CC_Texture0, cc_FragTexCoord1);
    
    gl_FragColor = textureColor;

}
