#include "Common.h"

using namespace std;
using namespace gl;
using namespace OVR;

class PostProcessDistortRift : public RiftRenderApp {
protected:
  Texture2dPtr textures[2];
  GeometryPtr quadGeometry;
  ProgramPtr program;

public:

  void initGl() {
    RiftRenderApp::initGl();
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glm::ivec2 imageSize;
    GlUtils::getImageAsTexture(textures[0],
        Resource::IMAGES_TUSCANY_UNDISTORTED_LEFT_PNG,
        imageSize);
    GlUtils::getImageAsTexture(textures[1],
        Resource::IMAGES_TUSCANY_UNDISTORTED_RIGHT_PNG,
        imageSize);

    quadGeometry = GlUtils::getQuadGeometry();

  }

  void draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    program =  GlUtils::getProgram(
      Resource::SHADERS_EXAMPLE_5_1_3_VS,
      Resource::SHADERS_EXAMPLE_5_1_3_FS);
    program->use();
    bindUniforms(program);
//    program->setUniform("LensOffset", lensOffset);
//    program->setUniform("ViewportAspectRatio", glm::aspect(eyeSize));
    quadGeometry->bindVertexArray();

    for (int i = 0; i < 2; ++i) {
      eye[i].viewport();
      eye[i].bindUniforms(program);
      textures[i]->bind();
      quadGeometry->draw();
    }

    VertexArray::unbind();
    Texture2d::unbind();
    Program::clear();
  }
};

RUN_OVR_APP(PostProcessDistortRift)