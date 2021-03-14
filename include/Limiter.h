#pragma once

#include <stdint.h>

namespace RQEngine
{

    class Limiter {

        public:
            Limiter();

            void setFPSTarget(int target);

            int currentFPS();

            uint32_t startFrame();
            void update();
            void limit();

        private:

            int targetFPS;
            uint32_t targetFrameTime;

            uint32_t startFrameTime;
            uint32_t previousFrameTime;

            uint32_t frameCount;
            uint32_t lastFrameSample;
            float currentFPSEstimate;

    };

} // namespace RQEngine
