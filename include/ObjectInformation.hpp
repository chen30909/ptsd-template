#include <string>
#include <glm/vec2.hpp>

#pragma once

class Objectinformation {
    public:
        Objectinformation( int Stage = 0 )
            : m_Stage(Stage) {
                this->InitialNeiber();
            }
        void InitialNeiber() {
            for ( int i = 0 ; i < 6 ; ++i ) {
                this->m_Neibor[i] = -1;
            }
        }
        
        int GetStage() { return this->m_Stage; }

        int GetPositionNumber() { return this->m_PosNumber; }

        int* GetNeibor() { return this->m_Neibor; }

        glm::vec2 GetPosition() { return this->m_Position; };
        
        
        void SetPosNumber( int PosNumber ) { 
            this->m_PosNumber = PosNumber;
        }

        void SetNeibor(int *Neibor ) {
            for ( int i = 0 ; i < 6 ; ++i ) {
                this->m_Neibor[i] = Neibor[i];
            }
        }
        
        void SetNeibor( int Neibor, int Dimension ) {
            this->m_Neibor[Dimension] = Neibor;
        }

        void SetStage( int Stage ) {
            this->m_Stage = Stage;
        }

        void SetPosition( glm::vec2 Postion ) {
            this->m_Position = Postion;
        }

    private:
        int m_Stage = 0 ;
        int m_PosNumber = 0 ;
        int m_Neibor[6] = {0};
        glm::vec2 m_Position = {0, 0};
};