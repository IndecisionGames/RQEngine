#pragma once

namespace RQEngine {

    class Block {
        public:
            Block(int type=-1);
            ~Block();
            bool isActive(){return m_active;};
            void setActive(bool active){m_active = active;};
            int getType(){return m_type;};
            void setType(int type){m_type = type;};
            int BLOCK_RENDER_SIZE = 1;
        
        private:
            bool m_active;
            int m_type;
    };

} // namespace RQEngine