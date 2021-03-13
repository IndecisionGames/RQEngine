namespace RQEngine
{
    
    class Game {

        public:
            Game();
            ~Game();

            void run();
            void exit();


            virtual void onInit() = 0;
            virtual void onExit() = 0;

            virtual void fixedUpdate(float deltaTime) = 0;
            virtual void update() = 0;

            virtual void draw() = 0;


        private:

            void init();
    };


} // namespace RQEngine