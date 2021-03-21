#pragma once

#include <unordered_map>


namespace RQEngine
{

    class KeyBinds {

        public:

            static KeyBinds* getInstance();
            
            static void load(unsigned int customKeyID, unsigned int key);
            static void update(unsigned int customKeyID, unsigned int key);

            static unsigned int getKey(unsigned int customKeyID);

        private:

            KeyBinds();

            static KeyBinds* instance;

            static std::unordered_map<unsigned int, unsigned int> keyBindingMap;

    };

} // namespace RQEngine
