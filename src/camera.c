#include "sf/camera.h"

#include "sf/shaders.h"

sf_camera sf_camera_perspective(float fov, float aspect, float near, float far) {
    sf_camera cam = {
        .type = SF_CAMERA_PERSPECTIVE,
        .transform = SF_TRANSFORM_IDENTITY,
        .fov = fov,
    };
    glm_perspective(glm_rad(fov), aspect, near, far, cam.projection);
    glGenFramebuffers(1, &cam.framebuffer);
    return cam;
}

sf_camera sf_camera_ortho(float left, float right, float bottom, float top, float near, float far) {
    sf_camera cam = {
        .type = SF_CAMERA_ORTHOGRAPHIC,
        .transform = SF_TRANSFORM_IDENTITY,
        .fov = 0,
    };
    glm_ortho(left, right, bottom, top, near, far, cam.projection);
    glGenFramebuffers(1, &cam.framebuffer);
    return cam;
}

void sf_camera_free(const sf_camera *camera) {
    glDeleteFramebuffers(1, &camera->framebuffer);
}

sf_vec3 sf_camera_right(const sf_camera *camera) {
    mat4 mat;
    sf_transform_view(mat, camera->transform);

    vec3 vec = {mat[0][0], mat[0][1], mat[0][2]};
    glm_vec3_normalize(vec);

    return (sf_vec3){vec[0], vec[1], vec[2]};
}

sf_vec3 sf_camera_forward(const sf_camera *camera) {
    mat4 mat;
    sf_transform_view(mat, camera->transform);

    vec3 vec = {mat[2][0], mat[2][1], mat[2][2]};
    glm_vec3_normalize(vec);

    return (sf_vec3){vec[0], vec[1], vec[2]};
}
