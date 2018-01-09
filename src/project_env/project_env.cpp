#include "project_env.h"
#include "file/file.h"
#include "yaml-cpp/yaml.h"

using namespace std;
using namespace json11;


ProjectDetails ProjectEnv::current() {
  return instance()->_current();
}

#pragma mark -  Private
ProjectEnv *ProjectEnv::instance_ = 0;

ProjectEnv *ProjectEnv::instance() {
  if (instance_ == 0) {
    instance_ = new ProjectEnv();
  }

  return instance_;
}

ProjectEnv::ProjectEnv() {}

ProjectDetails ProjectEnv::_current() {
  string path = FileManager::cwd() + "/metis.config.yml";

  return parse_project(path);
}

ProjectDetails ProjectEnv::parse_project(string path) {
  ProjectDetails details;
  
  string config_path  = path + "/metis.config.yml";
  YAML::Node prj      = YAML::LoadFile(config_path);

  const string token      = prj["project_token"].as<string>();
  const string name       = prj["name"].as<string>();
  const string entrypoint = prj["entrypoint"].as<string>();

  details.token       = token;
  details.name        = name;
  details.entrypoint  = entrypoint;

  return details;
}
