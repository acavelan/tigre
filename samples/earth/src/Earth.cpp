#include "Earth.hpp"

Earth::Earth(RenderView *renderer, Content *content, Logger *logger) :
    _rdr(renderer), _content(content), _log(logger),
    _earthTex(0), _sphere(0), _shader(0), _angle(0.0f)
{
    _log->info("Earth::Earth(renderView, content, logger)\n");

    _sphere = loadSphere(8, 32, 32);
    _earthTex = loadTexture("content:textures/earth.jpg");
    _shader = loadShader("shaders:texture.vert", "shaders:texture.frag");
}

Earth::~Earth()
{
    _log->info("Earth::~Earth()\n");

    _rdr->destroy(_sphere);
    _rdr->destroy(_earthTex);
    _rdr->destroy(_shader);
}

void Earth::resize(int width, int height)
{
    _log->info("Earth::resize(%d, %d)\n", width, height);

    _rdr->setViewport(width, height);

    _view = lookAt(vec3(20.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
    _projection = perspective(radians(60.0f), (float)width / (float)height, 0.001f, 100000.f);

    _view2D = lookAt(vec3(0.0f, 0.0f, 5.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
    _projection2D = ortho(0.0f, (float)width, 0.0f, (float)height, 0.0f, 10.0f);
}

void Earth::update(float delta)
{
    _angle += delta * 15.0f;
    if(_angle > 360) _angle = 0;
}

void Earth::render()
{
    _rdr->clear(color::Black);
    _rdr->setShader(_shader, _projection, _view, color::White);

    // Earth
    mat4 model= rotate(mat4(1.0f), radians(23.0f), vec3(0.0f, 0.0f, 1.0f));
    model = rotate(model, radians(_angle), vec3(0.0f, 1.0f, 0.0f));

    _rdr->setMatrix4(shader::model, model);

    _rdr->bindTexture(_earthTex);
    _rdr->draw(_sphere);

    // Texture
    _rdr->setShader(_shader, _projection2D, _view2D, color::White);

    _rdr->bindTexture(_earthTex);
    _rdr->draw(_earthTex, Rectangle(0, 0, _earthTex->width/8, _earthTex->height/8));
}

ModelMesh* Earth::loadSphere(float radius, int lat, int lon)
{
    Sphere sphere(radius, lat, lon);
    return _rdr->createModelMesh(&sphere);
}

Texture2D* Earth::loadTexture(const std::string &filename)
{
    Image *image = _content->loadFromFile<Image>(filename);
    Texture2D *texture = _rdr->createTexture2D(image);

    release(image);

    return texture;
}

Shader* Earth::loadShader(const std::string &vertexFile, const std::string &fragmentFile)
{
    ShaderSource shaderSource;

    _content->loadFile(vertexFile, shaderSource.vertexShader);
    _content->loadFile(fragmentFile, shaderSource.fragmentShader);

    Shader *shader = _rdr->createShader(shaderSource);

    return shader;
}
