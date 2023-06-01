//! #version 120
//! #extension GL_EXT_geometry_shader4 : enable

vec4 RotateVector(vec4 vector, float angle)
{
	vec4 result = vector;
	result.x = vector.x * cos(angle) - vector.y * sin(angle);
	result.y = vector.x * sin(angle) + vector.y * cos(angle);

	return result;
}

void main()
{
	vec4 startPoint = gl_PositionIn[0];
	vec4 endPoint = gl_PositionIn[1];

	gl_Position = gl_ModelViewProjectionMatrix * startPoint;
	EmitVertex();
	gl_Position = gl_ModelViewProjectionMatrix * endPoint;
	EmitVertex();
	EndPrimitive();

	vec4 arrowVector = startPoint - endPoint;
	float proportionArrowTriangle = length(arrowVector) / 4;

	vec4 leftSideArrowTriangleVector = RotateVector(arrowVector, radians(-15.0)) * proportionArrowTriangle;
	vec4 rightSideArrowTriangleVector = RotateVector(arrowVector, radians(15.0)) * proportionArrowTriangle;

	gl_Position = gl_ModelViewProjectionMatrix * (endPoint + leftSideArrowTriangleVector);
	EmitVertex();
	gl_Position = gl_ModelViewProjectionMatrix * endPoint;
	EmitVertex();
	gl_Position = gl_ModelViewProjectionMatrix * (endPoint + rightSideArrowTriangleVector);
	EmitVertex();
	EndPrimitive();
}
