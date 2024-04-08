#pragma once
#include "cocos2d.h"

USING_NS_CC;
enum initWithX{
	INIT_WITH_FILE,
	INIT_WITH_SPRITE_FRAME_NAME,
};
class CIDTriangle /* final*/
{
public:
	CIDTriangle(){}
	/**virtual*/~CIDTriangle(){}//not use virtual destructor !
	CIDTriangle(short ID0, short ID1, short ID2){
		initMembers();
		init(ID0, ID1, ID2);
	}
	void init(short ID0, short ID1, short ID2){
		m_vID[0] = ID0;
		m_vID[1] = ID1;
		m_vID[2] = ID2;
	}
	short getvIDByIndex(int index)const {
		assert(index >= 0 && index < 3);
		return m_vID[index];
	}
	void setvIDByIndex(int index, short ID){
		assert(index >= 0 && index < 3);
		m_vID[index] = ID;
	}
protected:
	void initMembers(){
		m_vID[0] = m_vID[1] = m_vID[2] = 0;
	}
protected:
	short m_vID[3];

};

class CIDLine/* final*/
{
public:
	CIDLine(){}
	/**virtual*/~CIDLine(){}//not use virtual destructor !
	CIDLine(short ID0, short ID1){
		initMembers();
		init(ID0, ID1);
	}
	void init(short ID0, short ID1){
		m_vID[0] = ID0;
		m_vID[1] = ID1;
	}
	short getvIDByIndex(int index){
		assert(index >= 0 && index < 2);
		return m_vID[index];
	}
	void setvIDByIndex(int index, short ID){
		assert(index >= 0 && index < 2);
		m_vID[index] = ID;
	}
protected:
	void initMembers(){
		m_vID[0] = m_vID[1] = 0;
	}
protected:
	short m_vID[2];
};

class Cv2/* final*/
{
public:
	Cv2(){}
	Cv2(float _x, float _y){
		initMembers();
		init(_x, _y);
	}
	/**virtual*/~Cv2(){};//not use virtual destructor !
	void init(float x, float y){
		m_v[0] = x;
		m_v[1] = y;
	}
	void setx(float x){ m_v[0] = x; }
	void sety(float y){ m_v[1] = y; }
	float x()const{ return m_v[0]; }
	float y()const{ return m_v[1]; }
	float*getArray(){ return m_v; }
protected:
	void initMembers(){
		m_v[0] = m_v[1] = 0;
	}
protected:
	float m_v[2];

};

class Cv4 /*final*/
{
public:
	Cv4(){}
	Cv4(float x, float y, float z, float w){
		initMembers();
		init(x, y, z, w);
	}
	/**virtual*/~Cv4(){};//not use virtual destructor !
	void init(float x, float y, float z, float w){
		m_v[0] = x;
		m_v[1] = y;
		m_v[2] = z;
		m_v[3] = w;
	}
	float x()const{ return m_v[0]; }
	float y()const{ return m_v[1]; }
	float z()const{ return m_v[2]; }
	float w()const{ return m_v[3]; }
	void setx(float x){ m_v[0] = x; }
	void sety(float y){ m_v[1] = y; }
	void setz(float z){ m_v[2] = z; }
	void setw(float w){ m_v[3] = w; }
protected:
	void initMembers(){
		m_v[0] = 0;
		m_v[1] = 0;
		m_v[2] = 0;
		m_v[3] = 0;
	}
protected:
	float m_v[4];

};

class CindexVBO :public CCObject
{

public:
	CindexVBO(){
		posBuffer = 0;
		texCoordBuffer = 0;
		indexBuffer = 0;
		colorBuffer = 0;
		m_indexArrayLen = 0;
		m_posArrayLen = 0;
		m_texCoordArrayLen = 0;
		m_colorArrayLen = 0;
		init_dft();
	}

	virtual ~CindexVBO(){
		if (posBuffer != 0)glDeleteBuffers(1, &posBuffer);
		if (texCoordBuffer != 0)glDeleteBuffers(1, &texCoordBuffer);
		if (indexBuffer != 0)glDeleteBuffers(1, &indexBuffer);
		if (colorBuffer != 0)glDeleteBuffers(1, &colorBuffer);

	}

	static void enableAttribArray_position(bool isEnable){
		if (isEnable)glEnableVertexAttribArray(kCCVertexAttrib_Position);
		else glDisableVertexAttribArray(kCCVertexAttrib_Position);
	}
	static void enableAttribArray_texCoord(bool isEnable){
		if (isEnable)glEnableVertexAttribArray(kCCVertexAttrib_TexCoords);
		else glDisableVertexAttribArray(kCCVertexAttrib_TexCoords);
	}

	static void enableAttribArray_color(bool isEnable){
		if (isEnable)glEnableVertexAttribArray(kCCVertexAttrib_Color);
		else glDisableVertexAttribArray(kCCVertexAttrib_Color);
	}


	static bool isEnabledAttribArray_position(){
		GLint isEnabled;
		glGetVertexAttribiv(kCCVertexAttrib_Position, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &isEnabled);
		return (bool)isEnabled;
	}
	static bool isEnabledAttribArray_texCoord(){
		GLint isEnabled;
		glGetVertexAttribiv(kCCVertexAttrib_TexCoords, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &isEnabled);
		return (bool)isEnabled;
	}
	static bool isEnabledAttribArray_color(){
		GLint isEnabled;
		glGetVertexAttribiv(kCCVertexAttrib_Color, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &isEnabled);
		return (bool)isEnabled;
	}

	void submitPos(const std::vector<Cv2> &pointList, GLenum usage){
		m_posArrayLen = ((int)pointList.size()) * 2;
		if (m_posArrayLen == 0)return;
		glBindBuffer(GL_ARRAY_BUFFER, posBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*m_posArrayLen, &pointList.front(), usage);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void submitTexCoord(const std::vector<Cv2> &texCoordList, GLenum usage){
		m_texCoordArrayLen = ((int)texCoordList.size()) * 2;
		if (m_texCoordArrayLen == 0)return;
		glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*m_texCoordArrayLen, &texCoordList.front(), usage);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void submitColor(const std::vector<Cv4> &colorList, GLenum usage){
		m_colorArrayLen = ((int)colorList.size()) * 4;
		if (m_colorArrayLen == 0)return;
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*m_colorArrayLen, &colorList.front(), usage);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void submitIndex(const std::vector<CIDTriangle> &IDtriList, GLenum usage){//CIDTriangle's element must use short type
		m_indexArrayLen = ((int)IDtriList.size()) * 3;
		if (m_indexArrayLen == 0)return;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(short)*m_indexArrayLen, &IDtriList.front(), usage);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	void submitIndex(const std::vector<CIDLine> &IDlineList, GLenum usage){//CIDLine's element must use short type
		m_indexArrayLen = ((int)IDlineList.size()) * 2;
		if (m_indexArrayLen == 0)return;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(short)*m_indexArrayLen, &IDlineList.front(), usage);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	void submitIndex(const std::vector<short> &indexList, GLenum usage){//element must use short type
		m_indexArrayLen = ((int)indexList.size()) * 1;
		if (m_indexArrayLen == 0)return;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(short)*m_indexArrayLen, &indexList.front(), usage);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	void setPointer_position(){
		//set position format
		glBindBuffer(GL_ARRAY_BUFFER, posBuffer);
		glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void setPointer_texCoord(){
		//set texCoord format
		glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
		glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void setPointer_color(){
		///set color format
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void draw(GLenum mode){
		if (m_indexArrayLen == 0)return;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glDrawElements(mode, m_indexArrayLen, GL_UNSIGNED_SHORT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
protected:
	void init_dft(){
		genBuffers();
	}
	void genBuffers(){
		if (posBuffer == 0)glGenBuffers(1, &posBuffer);
		if (texCoordBuffer == 0)glGenBuffers(1, &texCoordBuffer);
		if (indexBuffer == 0)glGenBuffers(1, &indexBuffer);
		if (colorBuffer == 0)glGenBuffers(1, &colorBuffer);
	}
protected:
	GLuint posBuffer;
	GLuint texCoordBuffer;
	GLuint indexBuffer;
	GLuint colorBuffer;
	int m_indexArrayLen;
	int m_posArrayLen;
	int m_texCoordArrayLen;
	int m_colorArrayLen;
};

namespace ripple {
	class CrippleBuffer :public CCObject
	{
	public:
		std::vector<std::vector<float> > mat;
	};
}

class Cmesh :public CCObject
{
public:
	std::vector<Cv2> vlist;
	std::vector<Cv2> texCoordList;
	std::vector<Cv4> colorList;
	std::vector<CIDTriangle> IDtriList;
	void clear(){
		vlist.clear();
		texCoordList.clear();
		colorList.clear();
		IDtriList.clear();
	}
};

class CrippleSprite : public Sprite{
public:
	CrippleSprite(){
		m_indexVBO = NULL;
		m_mesh = NULL;
		m_srcBuffer = NULL;
		m_dstBuffer = NULL;
		m_nRow = 0;
		m_nCol = 0;
		m_rippleStrength = 8;
		m_isDrawDebug = false;
		m_time = 0;

	}
	virtual ~CrippleSprite(){
		if (m_indexVBO)m_indexVBO->release();
		if (m_mesh)m_mesh->release();
		if (m_srcBuffer)m_srcBuffer->release();
		if (m_dstBuffer)m_dstBuffer->release();
	}
	bool initWithX(int x,std::string texFileName, float gridSideLen);
	void draw(Renderer* renderer, const Mat4 &transform, uint32_t flags);
	void onDrawDebug(const Mat4 &transform, uint32_t flags);
	void onDraw(const Mat4 &transform, uint32_t flags);
	void drawWire();
	void update(float t);
	void doTouch(const CCPoint&touchPoint, float depth, float r);
	float getGridSideLen()const{ return m_gridSideLen; }
	void setIsDrawDebug(bool value){ m_isDrawDebug = value; }
	bool getIsDrawDebug()const{ return m_isDrawDebug; }
protected:
	void updateOnce();
protected:
	CindexVBO*m_indexVBO;
	Cmesh*m_mesh;
	ripple::CrippleBuffer*m_srcBuffer;
	ripple::CrippleBuffer*m_dstBuffer;
	float m_gridSideLen;
	int m_nRow;//grid row count
	int m_nCol;//grid col count
	std::vector<Cv2> m_texCoordList_store;
	float m_rippleStrength;
	bool m_isDrawDebug;
	float m_time;
	Vec2 M4TransV2(const Mat4&mat, const Vec2&v);
	CustomCommand _customCommand;
	CustomCommand _customCommand_debug;
};

class CGLProgramWithUnifos :public CCGLProgram
{
protected:
	std::map<std::string, GLint> m_unifoMap;
public:

	CGLProgramWithUnifos(){
	}
	virtual ~CGLProgramWithUnifos(){
	}
	void attachUniform(std::string unifoName){
		m_unifoMap[unifoName] = glGetUniformLocation(this->getProgram(), unifoName.c_str());
	}
	void passUnifoValue1f(std::string unifoName, GLfloat v);
	void passUnifoValue1i(std::string unifoName, GLint v);
	void passUnifoValueMatrixNfv(std::string unifoName, const GLfloat *array, int arrayLen);
	void passUnifoValueNfv(std::string unifoName, const GLfloat *array, int arrayLen);
	void passUnifoValueNfvN(std::string unifoName, const GLfloat*array, int arrayLen, int arrayCount);
	void passUnifoValueNiv(std::string unifoName, const GLint *array, int arrayLen);
	void passUnifoValueMatrixNfv(std::string unifoName, const std::vector<GLfloat>&valueList);
	void passUnifoValueNfv(std::string unifoName, const std::vector<GLfloat>&valueList);
	void passUnifoValueNiv(std::string unifoName, const std::vector<GLint>&valueList);

};