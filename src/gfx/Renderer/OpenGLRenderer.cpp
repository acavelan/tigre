/*
TIGRE (https://gitorious.org/tigre) is made available under the MIT License.

Copyright (c) 2012 - 2013 Aurélien Cavelan (razlock)

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <glm/gtc/matrix_transform.hpp>

#include "OpenGLRenderer.hpp"

namespace tigre
{
	namespace gfx
	{
		OpenGLRenderer::OpenGLRenderer(OpenGLContext *context) :
			_context(context)
		{
		}

		OpenGLRenderer::~OpenGLRenderer()
		{
			destroy();
		}
		
		void OpenGLRenderer::init()
		{
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_TEXTURE_2D);
			
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			
			static const GLfloat vertices[12] = {
				0.0f, 0.0f,
				0.0f, 1.0f,
				1.0f, 1.0f,
				1.0f, 0.0f
			};
			
			static const GLfloat texCoords[12] = {
				0.0f, 1.0f,
				0.0f, 0.0f,
				1.0f, 0.0f,
				1.0f, 1.0f
			};
			
			static const GLubyte indices[6] = {
				0, 1, 2, 0, 2, 3
			};
			
			glGenBuffers(3, _quad.vbo);
			glBindBuffer(GL_ARRAY_BUFFER, _quad.vbo[0]);
			glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
			
			glBindBuffer(GL_ARRAY_BUFFER, _quad.vbo[1]);
			glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), texCoords, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _quad.vbo[2]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLubyte), indices, GL_STATIC_DRAW);
		}
		
		void OpenGLRenderer::destroy()
		{
			glDeleteBuffers(3, _quad.vbo);
		}
		
		// Texture
		Texture2D* OpenGLRenderer::createTexture2D(Image *image)
		{
			Texture2D *texture = new Texture2D();
			
			texture->token = _glTextures.size();
			
			OpenGLTexture *glTexture = new OpenGLTexture();
			
			texture->width = image->width;
			texture->height = image->height;
			
			_glTextures.push_back(glTexture);
			
			glGenTextures(1, &glTexture->textureId);
			glBindTexture(GL_TEXTURE_2D, glTexture->textureId);
			
			glTexImage2D(GL_TEXTURE_2D, 
				0, 
				GL_RGB, 
				texture->width, 
				texture->height, 
				0, 
				GL_RGB, 
				GL_UNSIGNED_BYTE, 
				image->pixels
			);
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			
			glGenerateMipmap(GL_TEXTURE_2D);
			
			return texture;
		}
		
		void OpenGLRenderer::bindTexture(Texture2D *texture)
		{
			if(texture)
			{
				OpenGLTexture *glTexture = _glTextures[texture->token];
				OpenGLShader *shader = _context->getCurrentShader();
				
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, glTexture->textureId);
				glUniform1i(shader->ports[shader::texture0], 0);
			}
			else
				glBindTexture(GL_TEXTURE_2D, 0);
		}
		
		void OpenGLRenderer::draw(Texture2D *texture)
		{
			OpenGLShader *shader = _context->getCurrentShader();
			
			glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
			modelMat = glm::scale(modelMat, glm::vec3(texture->width, texture->height, 1.0f));
			
			_context->setMatrix4(shader::model, modelMat);
			
			glBindBuffer(GL_ARRAY_BUFFER, _quad.vbo[0]);
			glVertexAttribPointer(shader->ports[shader::position], 2, GL_FLOAT, GL_FALSE, 0, 0);
			
			glBindBuffer(GL_ARRAY_BUFFER, _quad.vbo[1]);
			glVertexAttribPointer(shader->ports[shader::texCoord], 2, GL_FLOAT, GL_FALSE, 0, 0);

			glEnableVertexAttribArray(shader->ports[shader::position]);
			glEnableVertexAttribArray(shader->ports[shader::texCoord]);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _quad.vbo[2]);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
		}
		
		void OpenGLRenderer::draw(Texture2D*, Rectangle target)
		{
			OpenGLShader *shader = _context->getCurrentShader();
		
			glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), glm::vec3((float)target.x, (float)target.y, 0.0f));
			modelMat = glm::scale(modelMat, glm::vec3((float)target.width, (float)target.height, 1.0f));
			
			_context->setMatrix4(shader::model, modelMat);
			
			glBindBuffer(GL_ARRAY_BUFFER, _quad.vbo[0]);
			glVertexAttribPointer(shader->ports[shader::position], 2, GL_FLOAT, GL_FALSE, 0, 0);
			
			glBindBuffer(GL_ARRAY_BUFFER, _quad.vbo[1]);
			glVertexAttribPointer(shader->ports[shader::texCoord], 2, GL_FLOAT, GL_FALSE, 0, 0);

			glEnableVertexAttribArray(shader->ports[shader::position]);
			glEnableVertexAttribArray(shader->ports[shader::texCoord]);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _quad.vbo[2]);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
		}
		
		void OpenGLRenderer::draw(Texture2D *texture, Rectangle origin, Rectangle target)
		{
			OpenGLShader *shader = _context->getCurrentShader();
			
			glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), glm::vec3((float)target.x, (float)target.y, 0.0f));
			modelMat = glm::scale(modelMat, glm::vec3((float)target.width, (float)target.height, 1.0f));
			
			_context->setMatrix4(shader::model, modelMat);
			
			glBindBuffer(GL_ARRAY_BUFFER, _quad.vbo[0]);
			glVertexAttribPointer(shader->ports[shader::position], 2, GL_FLOAT, GL_FALSE, 0, 0);

			const int width = texture->width;
			const int height = texture->height;
			
			const GLfloat texCoords[12] = {
				(float)origin.y/height, (float)origin.width/width,
				(float)origin.y/height, (float)origin.x/width,
				(float)origin.height/height, (float)origin.x/width,
				(float)origin.height/height, (float)origin.width/width
			};
			
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glVertexAttribPointer(shader->ports[shader::texCoord], 2, GL_FLOAT, GL_FALSE, 0, texCoords);

			glEnableVertexAttribArray(shader->ports[shader::position]);
			glEnableVertexAttribArray(shader->ports[shader::texCoord]);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _quad.vbo[2]);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
		}
		
		void OpenGLRenderer::destroy(Texture2D *texture)
		{
			if(texture)
			{
				OpenGLTexture *glTexture = _glTextures[texture->token];
				
				glDeleteTextures(1, &glTexture->textureId);
				
				delete glTexture;
				core::release(texture);
			}
		}
		
		// Mesh
		ModelMesh* OpenGLRenderer::createModelMesh(Mesh *mesh)
		{
			ModelMesh *model = new ModelMesh();
			
			model->token = _glModels.size();
			
			OpenGLModelMesh *glModel = new OpenGLModelMesh();
			
			model->vertexCount = mesh->vertexCount;
			model->normalCount = mesh->normalCount;
			model->texCoordCount = mesh->texCoordCount;
			model->indexCount = mesh->indexCount;
			
			_glModels.push_back(glModel);
			
			glGenBuffers(4, glModel->vbo);
			glBindBuffer(GL_ARRAY_BUFFER, glModel->vbo[0]);
			glBufferData(GL_ARRAY_BUFFER, mesh->vertexCount * sizeof(float), mesh->vertices, GL_STATIC_DRAW);

			glBindBuffer(GL_ARRAY_BUFFER, glModel->vbo[1]);
			glBufferData(GL_ARRAY_BUFFER, mesh->normalCount * sizeof(float), mesh->normals, GL_STATIC_DRAW);

			glBindBuffer(GL_ARRAY_BUFFER, glModel->vbo[2]);
			glBufferData(GL_ARRAY_BUFFER, mesh->texCoordCount * sizeof(float), mesh->texCoords, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glModel->vbo[3]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indexCount * sizeof(unsigned int), mesh->indices, GL_STATIC_DRAW);
			
			return model;
		}
		
				
		void OpenGLRenderer::draw(ModelMesh *model)
		{
			OpenGLModelMesh *glModel = _glModels[model->token];
			OpenGLShader *shader = _context->getCurrentShader();
			
			if(model->vertexCount && shader->ports[shader::position] >= 0)
			{
				glBindBuffer(GL_ARRAY_BUFFER, glModel->vbo[0]);
				glVertexAttribPointer(shader->ports[shader::position], 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(shader->ports[shader::position]);
			}
			
			if(model->normalCount && shader->ports[shader::normal] >= 0)
			{
				glBindBuffer(GL_ARRAY_BUFFER, glModel->vbo[1]);
				glVertexAttribPointer(shader->ports[shader::normal], 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(shader->ports[shader::normal]);
			}
			
			if(model->texCoordCount && shader->ports[shader::texCoord] >= 0)
			{
				glBindBuffer(GL_ARRAY_BUFFER, glModel->vbo[2]);
				glVertexAttribPointer(shader->ports[shader::texCoord], 2, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(shader->ports[shader::texCoord]);
			}
			
			if(model->indexCount)
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glModel->vbo[3]);
				glDrawElements(GL_TRIANGLES, model->indexCount, GL_UNSIGNED_INT, 0);
				//glDrawElements(GL_LINES, model->getMesh()->getIndexCount(), GL_UNSIGNED_INT, 0);
			}
		}
		
		void OpenGLRenderer::destroy(ModelMesh *model)
		{
			if(model)
			{
				OpenGLModelMesh *glModel = _glModels[model->token];
				
				glDeleteBuffers(4, glModel->vbo);
				
				delete glModel;
				
				core::release(model);
			}
		}
	}
}

