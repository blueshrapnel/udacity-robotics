#include <gazebo/gazebo.hh>

namespace gazebo {
    class WorldPluginHello : public WorldPlugin {
        public: WorldPluginHello() : WorldPlugin() {
            printf("Welcome to Karen's World!\n");
        }
        public: void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf) {
        }
    };
    GZ_REGISTER_WORLD_PLUGIN(WorldPluginHello)
}
