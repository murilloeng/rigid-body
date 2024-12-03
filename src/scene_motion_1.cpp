//inc
#include <cstdio>
#include <cstdlib>

//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Light/Lights.hpp"
#include "Canvas/Canvas/inc/Light/Ambient.hpp"
#include "Canvas/Canvas/inc/Objects/1D/Arc.hpp"
#include "Canvas/Canvas/inc/Light/Direction.hpp"
#include "Canvas/Canvas/inc/Objects/1D/Line.hpp"
#include "Canvas/Canvas/inc/Objects/1D/Arrow.hpp"
#include "Canvas/Canvas/inc/Objects/3D/Cylinder.hpp"
#include "Canvas/Canvas/inc/Objects/Image/Latex.hpp"

//managers
#include "Canvas/Managers/inc/GLFW.hpp"

//rigid-body
#include "rigid-body/inc/scenes.hpp"

//scene
static void scene_axes(canvas::Scene* scene)
{
	//data
	canvas::objects::Line* axes_1 = new canvas::objects::Line;
	canvas::objects::Line* axes_2 = new canvas::objects::Line;
	canvas::objects::Line* axes_3 = new canvas::objects::Line;
	canvas::objects::Arrow* arrows_1 = new canvas::objects::Arrow;
	canvas::objects::Arrow* arrows_2 = new canvas::objects::Arrow;
	canvas::objects::Arrow* arrows_3 = new canvas::objects::Arrow;
	//arrows
	arrows_1->width(0.05f);
	arrows_2->width(0.05f);
	arrows_3->width(0.05f);
	arrows_1->height(0.05f);
	arrows_2->height(0.05f);
	arrows_3->height(0.05f);
	arrows_1->path(axes_1);
	arrows_2->path(axes_2);
	arrows_3->path(axes_3);
	arrows_1->parameter(1.0f);
	arrows_2->parameter(1.0f);
	arrows_3->parameter(1.0f);
	arrows_1->color_stroke({0, 0, 0});
	arrows_2->color_stroke({0, 0, 0});
	arrows_3->color_stroke({0, 0, 0});
	//axes
	axes_1->color_stroke({0, 0, 0});
	axes_2->color_stroke({0, 0, 0});
	axes_3->color_stroke({0, 0, 0});
	axes_1->point(0, {-0.5f, +0.0f, +0.0f});
	axes_2->point(0, {+0.0f, -0.5f, +0.0f});
	axes_3->point(0, {+0.0f, +0.0f, -0.2f});
	axes_1->point(1, {+1.0f, +0.0f, +0.0f});
	axes_2->point(1, {+0.0f, +1.0f, +0.0f});
	axes_3->point(1, {+0.0f, +0.0f, +1.0f});
	//scene
	scene->add_object(axes_1);
	scene->add_object(axes_2);
	scene->add_object(axes_3);
	scene->add_object(arrows_1);
	scene->add_object(arrows_2);
	scene->add_object(arrows_3);
}
static void scene_cylinders(canvas::Scene* scene)
{
	//data
	const float a = 1.00;
	const float b = 0.50;
	const uint32_t nc = 40;
	canvas::objects::Cylinder* cylinders[nc];
	for(uint32_t i = 0; i < nc; i++) cylinders[i] = new canvas::objects::Cylinder;
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
	scene_labels(scene);
	scene_cylinders(scene);
	scene_tilted_axis(scene);
}

void scene_motion_1(int argc, char** argv)
{
	//data
	canvas::managers::GLFW app(argc, argv, "../Canvas/Canvas/shd/");
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