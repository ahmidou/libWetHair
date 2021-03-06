//
// This file is part of the libWetHair open source project
//
// The code is licensed solely for academic and non-commercial use under the
// terms of the Clear BSD License. The terms of the Clear BSD License are
// provided below. Other licenses may be obtained by contacting the faculty
// of the Columbia Computer Graphics Group or a Columbia University licensing officer.
//
// The Clear BSD License
//
// Copyright 2017 Yun (Raymond) Fei, Henrique Teles Maia, Christopher Batty,
// Changxi Zheng, and Eitan Grinspun
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted (subject to the limitations in the disclaimer
// below) provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//  list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//  this list of conditions and the following disclaimer in the documentation
//  and/or other materials provided with the distribution.
//
// * Neither the name of the copyright holder nor the names of its contributors may be used
//  to endorse or promote products derived from this software without specific
//  prior written permission.
//
// NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS
// LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
// GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
// OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
// DAMAGE.


#ifndef __TWO_D_SCENE_XML_PARSER_H__
#define __TWO_D_SCENE_XML_PARSER_H__

#include <Eigen/StdVector>

#include <iostream>
#include <fstream>
#include <limits>

#include "rapidxml.hpp"

#include "TwoDScene.h"

#include "StrandCompliantManager.h"
#include "CompliantImplicitEuler.h"

#include "SpringForce.h"
#include "LinearSpringForce.h"
#include "SimpleGravityForce.h"
#include "DragDampingForce.h"

#include "StringUtilities.h"
#include "RenderingUtilities.h"

#include "LinearBendingForce.h"

#include "TwoDSceneRenderer.h"
#include "ExecutableSimulation.h"
#include "TwoDimensionalDisplayController.h"
#include "ParticleSimulation.h"
#include "CylindricalShallowFlow.h"
#include "PolygonalCohesion.h"

#include "LevelSetForce.h"
#include "DER/StrandForce.h"
#include "DER/StrandParameters.h"

#include "Camera.h"
#include "fluidsim2D.h"
#include "fluidsim3D.h"

// REALLY USEFULL TODOs
//   TODO: Improve error messages to display all valid options, etc. Could define an option class that knows its valid options and bounds on values.

// LESS USEFULL TODOs
//   TODO: Write method for computing number of a given property
//   TODO: Add some additional error checking for repeat properties, etc
//   TODO: Abstract out common code
//   TODO: Check for invalid properties

class TwoDSceneXMLParser
{
public:
  
  void loadExecutableSimulation( const std::string& file_name, const char* memory_str,
                                const std::string& init_filename, bool simulate_comparison, bool rendering_enabled, ExecutableSimulation** execsim, renderingutils::Viewport& view, Camera& cam,
                                scalar& max_time, scalar& steps_per_sec_cap, renderingutils::Color& bgcolor, std::string& description, std::string& scenetag, bool& cam_inited, bool& view_inited );

  // TODO: NEED AN EIGEN_ALIGNED_THING_HERE ?
private:

  template<int DIM>
  void loadParticleSimulation( bool simulate_comparison, bool rendering_enabled, ExecutableSimulation** execsim,
                               renderingutils::Viewport& view, renderingutils::Color& bgcolor, rapidxml::xml_node<>* node, const std::string& init_filename  );
  
  void loadDERSimulation( bool simulate_comparison, bool rendering_enabled, ExecutableSimulation** execsim,
                               renderingutils::Viewport& view, renderingutils::Color& bgcolor, rapidxml::xml_node<>* node, const std::string& init_filename  );

  void loadXMLFile( const std::string& filename, std::vector<char>& xmlchars, rapidxml::xml_document<>& doc );
  
  void loadXMLFileFromMemory( const char* memory_str, std::vector<char>& xmlchars, rapidxml::xml_document<>& doc );

  bool loadTextFileIntoString( const std::string& filename, std::string& filecontents );
  
  void loadSimulationType( rapidxml::xml_node<>* node, std::string& simtype );
  
  template<int DIM>
  void loadLiquidParameter( rapidxml::xml_node<> *node, TwoDScene<DIM>& twoscene);
  
  template<int DIM>
  void loadFluidSim( rapidxml::xml_node<> *node, TwoDScene<DIM>& twoscene );
  
  template<int DIM>
  void loadLinearBendingForces( rapidxml::xml_node<>* node, TwoDScene<DIM>& twodscene );
  
  template<int DIM>
  void loadParticleEdges( rapidxml::xml_node<>* node, TwoDScene<DIM>& twodscene );
  
  void loadStrandParticleEdges( rapidxml::xml_node<>* node, TwoDScene<3>& scene );
  
  template<int DIM>
  void loadFlow( rapidxml::xml_node<>* node, TwoDScene<DIM>& twodscene );
  
  void loadSceneTag( rapidxml::xml_node<>* node, std::string& scenetag );
  
  template<int DIM>
  void loadSpringForces( rapidxml::xml_node<>* node, TwoDScene<DIM>& twodscene );
  
  void loadScripts( rapidxml::xml_node<>* node, std::vector<Script>& scripts );
  
  template<int DIM>
  void loadLinearSpringForces( rapidxml::xml_node<>* node, TwoDScene<DIM>& twodscene );
  
  template<int DIM>
  void loadDragDampingForces( rapidxml::xml_node<>* node, TwoDScene<DIM>& twodscene );
  
  template<int DIM>
  void loadIntegrator( rapidxml::xml_node<>* node, TwoDScene<DIM>& twodscene, SceneStepper<DIM>** scenestepper );
  
  template<int DIM>
  void loadStrandParameters( rapidxml::xml_node<>* node, TwoDScene<DIM>& scene );

  template<int DIM>
  void loadStrandForces( rapidxml::xml_node<>* node, TwoDScene<DIM>& scene );  

  void loadMaxTime( rapidxml::xml_node<>* node, scalar& max_t );
  
  void loadMaxSimFrequency( rapidxml::xml_node<>* node, scalar& max_freq );

  bool loadViewport( rapidxml::xml_node<> *node, renderingutils::Viewport &view);
  
  void loadBackgroundColor( rapidxml::xml_node<>* node, renderingutils::Color& color );
  
  void loadParticleColors( rapidxml::xml_node<>* node, std::vector<renderingutils::Color>& particle_colors );

  void loadEdgeColors( rapidxml::xml_node<>* node, std::vector<renderingutils::Color>& edge_colors );
  
  void loadSceneDescriptionString( rapidxml::xml_node<>* node, std::string& description_string );
  
  bool loadCamera( rapidxml::xml_node<>* node, Camera& camera );
};

#endif
