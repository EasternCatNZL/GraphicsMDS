#version 430 core

in vec2 TexCoord;
in vec3 outColor;
in vec3 NormVec;
in vec3 fragPosition;

out vec4 color;

uniform sampler2D Texture;
uniform sampler2D Texture2;

uniform float currentTime;

uniform vec3 lightColor;
uniform vec3 diffuseColor;
uniform vec3 objectColor;
uniform vec3 lightPosition;

uniform vec3 viewPosition;

void main()
{
    vec4 TextureColor = texture(Texture, TexCoord);
    //Ambient Light
    float ambientStrength = 0.4f;
    vec3 ambientValue = ambientStrength * TextureColor.rgb * lightColor;
    //Diffuse light
    vec3 normal = normalize(NormVec);
    vec3 lightDirection = normalize(lightPosition - fragPosition);
    float difference = max(dot(normal, lightDirection), 0.0f);
    vec3 diffuseLight = difference * TextureColor.rgb * diffuseColor;
    //Specular
    float specularStrength = 10.0f;
    vec3 viewDirection = normalize(viewPosition - fragPosition);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    vec3 halfVector = normalize(lightDirection + viewDirection);
    float spec = pow(max(dot(normal, halfVector), 0.0), 32);
    //float spec = pow(max(dot(viewDirection, reflectionDirection), 0.0), 32);
    vec3 specular = spec * lightColor * specularStrength;
    //Blend

    //Final color
    vec3 finalObjectLight = (ambientValue + diffuseLight + specular) * objectColor;
    color = vec4(finalObjectLight, 1.0f);
    //color = texture(Texture, TexCoord);// * vec4(ambientValue, 1.0f);

    //vec3 colorTemp = outColor * abs(sin(currentTime));
    //vec3 colorTemp = outColor * abs(sin(3));
    //color = vec4(colorTemp, 1.0f);
    //color = vec4(outColor, 1.0f);
}