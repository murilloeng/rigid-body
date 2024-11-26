//inc
#include <cstdio>
#include <cstdlib>

//canvas
#include "Canvas/inc/Scene/Scene.hpp"
#include "Canvas/inc/Light/Lights.hpp"
#include "Canvas/inc/Light/Ambient.hpp"
#include "Canvas/inc/Objects/1D/Arc.hpp"
#include "Canvas/inc/Light/Direction.hpp"
#include "Canvas/inc/Objects/1D/Line.hpp"
#include "Canvas/inc/Objects/1D/Arrow.hpp"
#include "Canvas/inc/Objects/3D/Cylinder.hpp"
#include "Canvas/inc/Objects/Image/Latex.hpp"

//managers
#include "Canvas/Managers/inc/GLFW.hpp"

//rigid-body
#include "rigid-body/inc/scenes.hpp"

//data
static const float a = 1.00;
static const float b = 0.50;
static const uint32_t nc = 40;
static canvas::objects::Line* axes[3];
static canvas::objects::Arrow* arrows[3];
static canvas::objects::Cylinder* cylinders[nc];

//scene
static void scene_axes(canvas::Scene* scene)
{
	//data
	axes[0] = new canvas::objects::Line;
	axes[1] = new canvas::objects::Line;
	axes[2] = new canvas::objects::Line;
	//axes
	axes[0]->color_stroke({0, 0, 0});
	axes[1]->color_stroke({0, 0, 0});
	axes[2]->color_stroke({0, 0, 0});
	axes[0]->point(0, {-0.5f, +0.0f, +0.0f});
	axes[1]->point(0, {+0.0f, -0.5f, +0.0f});
	axes[2]->point(0, {+0.0f, +0.0f, -0.2f});
	axes[0]->point(1, {+1.0f, +0.0f, +0.0f});
	axes[1]->point(1, {+0.0f, +1.0f, +0.0f});
	axes[2]->point(1, {+0.0f, +0.0f, +1.0f});
	//scene
	for(uint32_t i = 0; i < 3; i++)
	{
		scene->add_object(axes[i]);
	}
}
static void scene_arrows(canvas::Scene* scene)
{
	//data
	arrows[0] = new canvas::objects::Arrow;
	arrows[1] = new canvas::objects::Arrow;
	arrows[2] = new canvas::objects::Arrow;
	//arrows
	arrows[0]->width(0.05f);
	arrows[1]->width(0.05f);
	arrows[2]->width(0.05f);
	arrows[0]->height(0.05f);
	arrows[1]->height(0.05f);
	arrows[2]->height(0.05f);
	arrows[0]->path(axes[0]);
	arrows[1]->path(axes[1]);
	arrows[2]->path(axes[2]);
	arrows[0]->parameter(1.0f);
	arrows[1]->parameter(1.0f);
	arrows[2]->parameter(1.0f);
	arrows[0]->color_stroke({0, 0, 0});
	arrows[1]->color_stroke({0, 0, 0});
	arrows[2]->color_stroke({0, 0, 0});
	//scene
	for(uint32_t i = 0; i < 3; i++)
	{
		scene->add_object(arrows[i]);
	}
}
static void scene_cylinders(canvas::Scene* scene)
{
	//data
	for(uint32_t i = 0; i < nc; i++)
	{
		cylinders[i] = new canvas::objects::Cylinder;
	}
	//cylinders
	for(uint32_t i = 0; i < nc; i++)
	{
		const float t1 = float(i + 0) / nc;
		const float t2 = float(i + 1) / nc;
		const float x1 = 3 * t1 * (1 - t1) * (1 - t1) * a + t1 * t1 * (3 - 2 * t1);
		const float x2 = 3 * t2 * (1 - t2) * (1 - t2) * a + t2 * t2 * (3 - 2 * t2);
		const float y1 = 3 * t1 * (1 - t1) * (1 - t1) * a + 3 * t1 * t1 * (1 - t1) * b;
		const float y2 = 3 * t2 * (1 - t2) * (1 - t2) * a + 3 * t2 * t2 * (1 - t2) * b;
		cylinders[i]->stroke(false);
		cylinders[i]->radius(0, y1);
		cylinders[i]->radius(1, y2);
		cylinders[i]->height(x2 - x1);
		cylinders[i]->color_fill({0, 0, 1});
		cylinders[i]->apply_matrix(canvas::mat4());
		cylinders[i]->shift({0, 0, (x2 + x1) / 2});
		cylinders[i]->rotate({float(M_PI) / 4, 0, 0});
		cylinders[i]->scale(0.75f);
	}
	//scene
	for(uint32_t i = 0; i < nc; i++)
	{
		scene->add_object(cylinders[i]);
	}
}
static void scene_labels(canvas::Scene* scene)
{
	//data
	canvas::objects::Latex* label_2 = new canvas::objects::Latex;
	canvas::objects::Latex* label_3 = new canvas::objects::Latex;
	//latex
	scene->add_latex("$ x_2 $");
	scene->add_latex("$ x_3 $");
	//labels
	label_2->index(0);
	label_3->index(1);
	label_2->size(0.07f);
	label_3->size(0.07f);
	label_2->position({0, 1, 0});
	label_3->position({0, 0, 1});
	label_2->color_fill({0, 0, 0});
	label_3->color_fill({0, 0, 0});
	label_2->direction(0, {0, 1, 0});
	label_3->direction(0, {0, 1, 0});
	label_2->direction(1, {0, 0, 1});
	label_3->direction(1, {0, 0, 1});
	//scene
	scene->add_object(label_2);
	scene->add_object(label_3);
}
static void scene_tilted_axis(canvas::Scene* scene)
{
	//data
	const float r = 0.1f;
	const float a = -(float) M_PI_4;
	const float b = -(float) M_PI_2;
	canvas::objects::Arc* arc = new canvas::objects::Arc;
	canvas::objects::Line* line_1 = new canvas::objects::Line;
	canvas::objects::Line* line_2 = new canvas::objects::Line;
	canvas::objects::Arrow* head_1 = new canvas::objects::Arrow;
	canvas::objects::Arrow* head_2 = new canvas::objects::Arrow;
	canvas::objects::Latex* label_1 = new canvas::objects::Latex;
	canvas::objects::Latex* label_2 = new canvas::objects::Latex;
	//lines
	line_1->color_stroke({0, 0, 0});
	line_2->color_stroke({0, 0, 1});
	line_1->point(0, {0, +0.0f, +0.0f});
	line_1->point(1, {0, +0.2f, -0.2f});
	line_2->point(0, {0, -0.6f, +0.6f});
	line_2->point(1, {0, -0.7f, +0.7f});
	//heads
	head_1->path(line_2);
	head_2->path(line_2);
	head_1->width(0.03f);
	head_2->width(0.03f);
	head_1->height(0.03f);
	head_2->height(0.03f);
	head_1->parameter(0.8f);
	head_2->parameter(1.0f);
	head_1->color_stroke({0, 0, 1});
	head_2->color_stroke({0, 0, 1});
	//arc
	arc->radius(r);
	arc->angle(0, a);
	arc->angle(1, b);
	arc->base({0, 1, 0});
	arc->normal({1, 0, 0});
	arc->color_stroke({0, 0, 0});
	//labels
	label_1->size(0.10f);
	label_2->size(0.10f);
	label_1->anchor("NW");
	label_2->anchor("SE");
	label_1->color_fill({0, 0, 0});
	label_2->color_fill({0, 0, 1});
	label_1->direction(0, {0, 1, 0});
	label_2->direction(0, {0, 1, 0});
	label_1->direction(1, {0, 0, 1});
	label_2->direction(1, {0, 0, 1});
	label_2->position({0, -0.7f, +0.7f});
	label_1->index(scene->add_latex("$ \\beta $"));
	label_2->index(scene->add_latex("$ \\dot{\\varphi}_0 $"));
	label_1->position({0, r * cos((a + b) / 2), r * sin((a + b) / 2)});
	//scene
	scene->add_object(arc);
	scene->add_object(line_1);
	scene->add_object(line_2);
	scene->add_object(head_1);
	scene->add_object(head_2);
	scene->add_object(label_1);
	scene->add_object(label_2);
}
static void scene_setup(canvas::Scene* scene)
{
	//light
	glLineWidth(2);
	scene->background({1, 1, 1});
	scene->light().add_direction();
	scene->light().ambient()->color({0.3f, 0.3f, 0.3f});
	scene->light().direction(0)->color({0.7f, 0.7f, 0.7f});
	scene->light().direction(0)->direction({0.0f, 1.0f, 0.0f});
	scene->light().update_shaders();
	//objects
	scene_axes(scene);
	scene_arrows(scene);
	scene_labels(scene);
	scene_cylinders(scene);
	scene_tilted_axis(scene);
}

void scene_motion(int argc, char** argv)
{
	//data
	canvas::managers::GLFW app(argc, argv, "../Canvas/shd/");
	//scene
	scene_setup(app.scene());
	canvas::Scene* scene = app.scene();
	//update
	scene->update(true);
	scene->camera().bound();
	scene->camera().apply();
	scene->camera().update();
	//start
	app.start();
}