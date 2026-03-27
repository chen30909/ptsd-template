#include "StageObject.hpp"
#include "App.hpp"
#include "Global.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <random>
#include <thread>
#include <vector>
#include <chrono>

void StageObject::MakeDisappearWithObject( int current_pos ) {
    if ( m_Stage_Object[current_pos]->GetVisibility() == false ) {
        return;
    }

    switch ( m_Stage_Object[current_pos]->GetCurrentType() ) {
        case FLOWER_COMBINED_OBJECT:
            MakeDisappearWithFlowerCombined( current_pos );
        break;
        case FLOWER_STRIPE_OBJECT:
            MakeDisappearWithStripeFlower( current_pos );
        break;
        case STRIPE_COMBINED_OBJECT:
            MakeDisappearWithStripeCombined( current_pos );
        break;
        case STRIPE_OBJECT:
            MakeDisappearWithStripe( current_pos );
            break;
        case STRIPE_LEFT_RIGHT_OBJECT:
            MakeDisappearWithStripeInLeftRight( current_pos );
            break;
        case STRIPE_RIGHT_LEFT_OBJECT:
            MakeDisappearWithStripeInRightLeft( current_pos );
            break;
        case RAINBOWBALL_OBJECT:
            MakeDisappearWithRainbow( current_pos );
            break;
        case FLOWER_OBJECT:
            MakeDisappearWithFlower( current_pos );
            break;
        case TRIANGLEFLOWER_OBJECT:
            MakeDisappearWithTriangleFlower( current_pos );
            break;
        case STARFLOWER_OBJECT:
            MakeDisappearWithStarFlower( current_pos );
            break;
        case NORMAL_OBJECT:
            m_Stage_Object[current_pos]->DisAppear();
            m_Stage_Object[current_pos]->SetAppearBool( false );
            break;
        case ONE_LAYER_COOKIE_OBJECT:
            // m_Stage_Object[current_pos]->DisAppear();
            m_Stage_Object[current_pos]->SetAppearBool( false );
            // m_Stage_Object[current_pos]->SetCurrentType( NORMAL_OBJECT );
            break;
        case TWO_LAYER_COOKIE_OBJECT:
            // m_Stage_Object[current_pos]->DisAppear();
            m_Stage_Object[current_pos]->SetAppearBool( false );
            break;
        default:
            m_Stage_Object[current_pos]->DisAppear();
            m_Stage_Object[current_pos]->SetAppearBool( false );
            break;
    }
}

void StageObject::MakeDisappearWithStripe( int current_pos ) {
    m_Stage_Object[current_pos]->DisAppear();
    m_Stage_Object[current_pos]->SetAppearBool( false );
    // cout << "STRIPE\n";
    for ( int i = current_pos , j = current_pos ; ; ) {
        if ( m_Stage_Object[i]->GetInformationNeibor()[0]%(m_Size+1) != -1 ) {
            MakeDisappearWithObject( m_Stage_Object[i]->GetInformationNeibor()[0]%(m_Size+1) );
            i = m_Stage_Object[i]->GetInformationNeibor()[0]%(m_Size+1);
        }
        if ( m_Stage_Object[j]->GetInformationNeibor()[3]%(m_Size+1) != -1 ) {
            MakeDisappearWithObject( m_Stage_Object[j]->GetInformationNeibor()[3]%(m_Size+1) );
            j = m_Stage_Object[j]->GetInformationNeibor()[3]%(m_Size+1);
        }
        if ( m_Stage_Object[i]->GetInformationNeibor()[0]%(m_Size+1) == -1 && m_Stage_Object[j]->GetInformationNeibor()[3]%(m_Size+1) == -1 )
            break;
    }
}
void StageObject::MakeDisappearWithFlowerCombined( int current_pos ) {
    m_Stage_Object[current_pos]->DisAppear();
    m_Stage_Object[current_pos]->SetAppearBool( false );

    // // cout << "FLOWER_COMBINED\n";

    for ( int i = 0 ; i < 6 ; ++i )
    {
        if (m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1) != -1)
        {
            MakeDisappearWithObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1)  );

            for ( int j = 0 ; j < 6 ; ++j ) {
                if (m_Stage_Object[ m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1) ] ->GetInformationNeibor()[j]%(m_Size+1) != -1)
                {
                    MakeDisappearWithObject( m_Stage_Object[ m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1) ] ->GetInformationNeibor()[j]%(m_Size+1)  );

                }
            }
        }
    }
}

void StageObject::MakeDisappearWithStripeFlower( int current_pos ) {
    m_Stage_Object[current_pos]->DisAppear();
    m_Stage_Object[current_pos]->SetAppearBool( false );
    // // cout << "STRIPE_FLOWER\n";
    int side = -1;
    if ( m_Stage_Object[current_pos]->GetType() == STRIPE_OBJECT )
    {
        side = 0 ;
    }
    else if (m_Stage_Object[current_pos]->GetType() == STRIPE_LEFT_RIGHT_OBJECT )
    {
        side = 2 ;
    }
    else if (m_Stage_Object[current_pos]->GetType() == STRIPE_RIGHT_LEFT_OBJECT )
    {
        side = 1 ;
    }
    m_Stage_Object[current_pos]->SetBlockType(NORMAL_OBJECT);
    // // cout << "side: " << side << std::endl;
    for ( int i = current_pos , j = current_pos ; ; ) {
        switch (side)
        {
            case 0:
                if ( m_Stage_Object[i]->GetInformationNeibor()[0]%(m_Size+1) != -1 ) {
                    MakeDisappearWithObject( m_Stage_Object[i]->GetInformationNeibor()[0]%(m_Size+1) );

                    if ( m_Stage_Object[i]->GetInformationNeibor()[1]%(m_Size+1) != -1 )
                        MakeDisappearWithStripe( m_Stage_Object[i]->GetInformationNeibor()[1]%(m_Size+1) );
                    if ( m_Stage_Object[i]->GetInformationNeibor()[2]%(m_Size+1) != -1 )
                        MakeDisappearWithStripe( m_Stage_Object[i]->GetInformationNeibor()[2]%(m_Size+1) );
                    if ( m_Stage_Object[i]->GetInformationNeibor()[4]%(m_Size+1) != -1 )
                        MakeDisappearWithStripe( m_Stage_Object[i]->GetInformationNeibor()[4]%(m_Size+1) );
                    if ( m_Stage_Object[i]->GetInformationNeibor()[5]%(m_Size+1) != -1 )
                        MakeDisappearWithStripe( m_Stage_Object[i]->GetInformationNeibor()[5]%(m_Size+1) );
                    i = m_Stage_Object[i]->GetInformationNeibor()[0]%(m_Size+1);
                }
                if ( m_Stage_Object[j]->GetInformationNeibor()[3]%(m_Size+1) != -1 ) {
                    MakeDisappearWithObject( m_Stage_Object[j]->GetInformationNeibor()[3]%(m_Size+1) );

                    if ( m_Stage_Object[j]->GetInformationNeibor()[1]%(m_Size+1) != -1 )
                        MakeDisappearWithStripe( m_Stage_Object[j]->GetInformationNeibor()[1]%(m_Size+1) );
                    if ( m_Stage_Object[j]->GetInformationNeibor()[2]%(m_Size+1) != -1 )
                        MakeDisappearWithStripe( m_Stage_Object[j]->GetInformationNeibor()[2]%(m_Size+1) );
                    if ( m_Stage_Object[j]->GetInformationNeibor()[4]%(m_Size+1) != -1 )
                        MakeDisappearWithStripe( m_Stage_Object[j]->GetInformationNeibor()[4]%(m_Size+1) );
                    if ( m_Stage_Object[j]->GetInformationNeibor()[5]%(m_Size+1) != -1 )
                        MakeDisappearWithStripe( m_Stage_Object[j]->GetInformationNeibor()[5]%(m_Size+1) );
                    j = m_Stage_Object[j]->GetInformationNeibor()[3]%(m_Size+1);
                }
                break;
            case 1:
                if ( m_Stage_Object[i]->GetInformationNeibor()[1]%(m_Size+1) != -1 ) {
                    // // cout << i << endl;
                    MakeDisappearWithObject( m_Stage_Object[i]->GetInformationNeibor()[1]%(m_Size+1) );

                    if ( m_Stage_Object[i]->GetInformationNeibor()[0]%(m_Size+1) != -1 )
                        MakeDisappearWithStripeInRightLeft( m_Stage_Object[i]->GetInformationNeibor()[0]%(m_Size+1) );
                    if ( m_Stage_Object[i]->GetInformationNeibor()[2]%(m_Size+1) != -1 )
                        MakeDisappearWithStripeInRightLeft( m_Stage_Object[i]->GetInformationNeibor()[2]%(m_Size+1) );
                    if ( m_Stage_Object[i]->GetInformationNeibor()[3]%(m_Size+1) != -1 )
                        MakeDisappearWithStripeInRightLeft( m_Stage_Object[i]->GetInformationNeibor()[3]%(m_Size+1) );
                    if ( m_Stage_Object[i]->GetInformationNeibor()[5]%(m_Size+1) != -1 )
                        MakeDisappearWithStripeInRightLeft( m_Stage_Object[i]->GetInformationNeibor()[5]%(m_Size+1) );
                    i = m_Stage_Object[i]->GetInformationNeibor()[1]%(m_Size+1);
                    
                }
                if ( m_Stage_Object[j]->GetInformationNeibor()[4]%(m_Size+1) != -1 ) {
                    // // cout << j << endl;
                    MakeDisappearWithObject( m_Stage_Object[j]->GetInformationNeibor()[4]%(m_Size+1) );

                    if ( m_Stage_Object[j]->GetInformationNeibor()[0]%(m_Size+1) != -1 )
                        MakeDisappearWithStripeInRightLeft( m_Stage_Object[j]->GetInformationNeibor()[0]%(m_Size+1) );
                    if ( m_Stage_Object[j]->GetInformationNeibor()[2]%(m_Size+1) != -1 )
                        MakeDisappearWithStripeInRightLeft( m_Stage_Object[j]->GetInformationNeibor()[2]%(m_Size+1) );
                    if ( m_Stage_Object[j]->GetInformationNeibor()[3]%(m_Size+1) != -1 )
                        MakeDisappearWithStripeInRightLeft( m_Stage_Object[j]->GetInformationNeibor()[3]%(m_Size+1) );
                    if ( m_Stage_Object[j]->GetInformationNeibor()[5]%(m_Size+1) != -1 )
                        MakeDisappearWithStripeInRightLeft( m_Stage_Object[j]->GetInformationNeibor()[5]%(m_Size+1) );
                    j = m_Stage_Object[j]->GetInformationNeibor()[4]%(m_Size+1);
                    
                }
                break;
            case 2:
                if ( m_Stage_Object[i]->GetInformationNeibor()[2]%(m_Size+1) != -1 ) {
                    MakeDisappearWithObject( m_Stage_Object[i]->GetInformationNeibor()[2]%(m_Size+1) );

                    if ( m_Stage_Object[i]->GetInformationNeibor()[0]%(m_Size+1) != -1 )
                        MakeDisappearWithStripeInLeftRight( m_Stage_Object[i]->GetInformationNeibor()[0]%(m_Size+1) );
                    if ( m_Stage_Object[i]->GetInformationNeibor()[1]%(m_Size+1) != -1 )
                        MakeDisappearWithStripeInLeftRight( m_Stage_Object[i]->GetInformationNeibor()[1]%(m_Size+1) );
                    if ( m_Stage_Object[i]->GetInformationNeibor()[3]%(m_Size+1) != -1 )
                        MakeDisappearWithStripeInLeftRight( m_Stage_Object[i]->GetInformationNeibor()[3]%(m_Size+1) );
                    if ( m_Stage_Object[i]->GetInformationNeibor()[4]%(m_Size+1) != -1 )
                        MakeDisappearWithStripeInLeftRight( m_Stage_Object[i]->GetInformationNeibor()[4]%(m_Size+1) );
                    i = m_Stage_Object[i]->GetInformationNeibor()[2]%(m_Size+1);
                    
                }
                if ( m_Stage_Object[j]->GetInformationNeibor()[5]%(m_Size+1) != -1 ) {
                    MakeDisappearWithObject( m_Stage_Object[j]->GetInformationNeibor()[5]%(m_Size+1) );

                    if ( m_Stage_Object[j]->GetInformationNeibor()[0]%(m_Size+1) != -1 )
                        MakeDisappearWithStripeInLeftRight( m_Stage_Object[j]->GetInformationNeibor()[0]%(m_Size+1) );
                    if ( m_Stage_Object[j]->GetInformationNeibor()[1]%(m_Size+1) != -1 )
                        MakeDisappearWithStripeInLeftRight( m_Stage_Object[j]->GetInformationNeibor()[1]%(m_Size+1) );
                    if ( m_Stage_Object[j]->GetInformationNeibor()[3]%(m_Size+1) != -1 )
                        MakeDisappearWithStripeInLeftRight( m_Stage_Object[j]->GetInformationNeibor()[3]%(m_Size+1) );
                    if ( m_Stage_Object[j]->GetInformationNeibor()[4]%(m_Size+1) != -1 )
                        MakeDisappearWithStripeInLeftRight( m_Stage_Object[j]->GetInformationNeibor()[4]%(m_Size+1) );
                    j = m_Stage_Object[j]->GetInformationNeibor()[5]%(m_Size+1);
                    
                }
                break;
            default:
                break;
        }
        
        if ( m_Stage_Object[i]->GetInformationNeibor()[side]%(m_Size+1) == -1 && m_Stage_Object[j]->GetInformationNeibor()[side+3]%(m_Size+1) == -1 )
            break;
    }
}

void StageObject::MakeDisappearWithStripeCombined( int current_pos ) {
    m_Stage_Object[current_pos]->DisAppear();
    m_Stage_Object[current_pos]->SetAppearBool( false );
    // // cout << "STRIPE_COMBINED"<<endl;

    int side = -1 ;
    if (m_Stage_Object[current_pos]->GetType() == STRIPE_OBJECT )
    {
        side = 0 ;
    }
    else if (m_Stage_Object[current_pos]->GetType() == STRIPE_LEFT_RIGHT_OBJECT )
    {
        side = 2 ;
    }
    else if (m_Stage_Object[current_pos]->GetType() == STRIPE_RIGHT_LEFT_OBJECT )
    {
        side = 1 ;
    }
    m_Stage_Object[current_pos]->SetBlockType(NORMAL_OBJECT);

    for ( int i = current_pos , j = current_pos ; ; ) {
        if ( m_Stage_Object[i]->GetInformationNeibor()[side]%(m_Size+1) != -1 ) {
            MakeDisappearWithObject( m_Stage_Object[i]->GetInformationNeibor()[side]%(m_Size+1) );
            i = m_Stage_Object[i]->GetInformationNeibor()[side]%(m_Size+1);
        }
        if ( m_Stage_Object[j]->GetInformationNeibor()[side+3]%(m_Size+1) != -1 ) {
            MakeDisappearWithObject( m_Stage_Object[j]->GetInformationNeibor()[side+3]%(m_Size+1) );
            j = m_Stage_Object[j]->GetInformationNeibor()[side+3]%(m_Size+1);
        }
        if ( m_Stage_Object[i]->GetInformationNeibor()[side]%(m_Size+1) == -1 && m_Stage_Object[j]->GetInformationNeibor()[side+3]%(m_Size+1) == -1 )
            break;
    }


}

void StageObject::MakeDisappearWithStripeInLeftRight( int current_pos ) {
    m_Stage_Object[current_pos]->DisAppear();
    m_Stage_Object[current_pos]->SetAppearBool( false );
    // // cout << "STRIPE_LEFT_RIGHT\n";
    for ( int i = current_pos , j = current_pos ; ; ) {
        if ( m_Stage_Object[i]->GetInformationNeibor()[2]%(m_Size+1) != -1 ) {
            MakeDisappearWithObject( m_Stage_Object[i]->GetInformationNeibor()[2]%(m_Size+1) );
            i = m_Stage_Object[i]->GetInformationNeibor()[2]%(m_Size+1);
        }
        if ( m_Stage_Object[j]->GetInformationNeibor()[5]%(m_Size+1) != -1 ) {
            MakeDisappearWithObject( m_Stage_Object[j]->GetInformationNeibor()[5]%(m_Size+1)  );
            j = m_Stage_Object[j]->GetInformationNeibor()[5]%(m_Size+1);
        }
        if ( m_Stage_Object[i]->GetInformationNeibor()[2]%(m_Size+1) == -1 && m_Stage_Object[j]->GetInformationNeibor()[5]%(m_Size+1) == -1 )
            break;
    }
}

void StageObject::MakeDisappearWithStripeInRightLeft( int current_pos ) {
    m_Stage_Object[current_pos]->DisAppear();
    m_Stage_Object[current_pos]->SetAppearBool( false );
    // // cout << "STRIPE_RIGHT_LEFT\n";
    for ( int i = current_pos , j = current_pos ; ; ) {
        if ( m_Stage_Object[i]->GetInformationNeibor()[1]%(m_Size+1) != -1 ) {
            MakeDisappearWithObject( m_Stage_Object[i]->GetInformationNeibor()[1]%(m_Size+1) );
            i = m_Stage_Object[i]->GetInformationNeibor()[1]%(m_Size+1);
        }
        if ( m_Stage_Object[j]->GetInformationNeibor()[4]%(m_Size+1) != -1 ) {
            MakeDisappearWithObject( m_Stage_Object[j]->GetInformationNeibor()[4]%(m_Size+1) );
            j = m_Stage_Object[j]->GetInformationNeibor()[4]%(m_Size+1);
        }
        if ( m_Stage_Object[i]->GetInformationNeibor()[1]%(m_Size+1) == -1 && m_Stage_Object[j]->GetInformationNeibor()[4]%(m_Size+1) == -1 )
            break;
    }
}

void StageObject::MakeDisappearWithRainbow( int current_pos ) { //get type: next move
    m_Stage_Object[current_pos]->DisAppear();
    m_Stage_Object[current_pos]->SetAppearBool( false );

    if ( m_Stage_Object[current_pos]->GetBlockType() == 0 ) { // no color
        m_Stage_Object[current_pos]->SetBlock( BLUE_OBJECT );
    }

    // // cout << "RAINBOW BALL\n";

    if (m_Stage_Object[current_pos]->GetType() == RAINBOWBALL_OBJECT) {
        for ( int i = 1 ; i < m_Size+1 ; ++i ) {
                MakeDisappearWithObject( i );
        }
        return ;
    }

    if (m_Stage_Object[current_pos]->GetType() != 0) {
        // change same color to special type
        for ( int i = 1 ; i < m_Size+1 ; ++i ) {
            if ( i != current_pos && m_Stage_Object[current_pos]->GetBlockType() == m_Stage_Object[i]->GetBlockType() ) {
                //random

                if (m_Stage_Object[current_pos]->GetType() >=2 && m_Stage_Object[current_pos]->GetType() <=4) {
                    std::random_device rd;  // 硬體隨機數產生器
                    std::mt19937 gen(rd()); // Mersenne Twister 亂數引擎
                    std::uniform_int_distribution<int> dist(2, 4); // 產生 2 到 4 之間的整數

                    int random_number = dist(gen);

                    m_Stage_Object[i]->SetCurrentType( random_number );
                }
                    m_Stage_Object[i]->SetCurrentType( m_Stage_Object[current_pos]->GetType() );
            }
        }
    }

    m_Stage_Object[current_pos]->SetBlockType(NORMAL_OBJECT);

    for ( int i = 1 ; i < m_Size+1 ; ++i ) {
        if ( i != current_pos && m_Stage_Object[current_pos]->GetBlockType() == m_Stage_Object[i]->GetBlockType() ) {

            MakeDisappearWithObject( i );
            for ( int j = 0 ; j < 6 ; ++j ) {
                if (m_Stage_Object[i]->GetInformationNeibor()[j]%(m_Size+1) != -1 && m_Stage_Object[i]->GetCurrentType() == NORMAL_OBJECT){

                    if (  m_Stage_Object[m_Stage_Object[i]->GetInformationNeibor()[j]%(m_Size+1)]->GetCurrentType() == ONE_LAYER_COOKIE_OBJECT || m_Stage_Object[m_Stage_Object[i]->GetInformationNeibor()[j]%(m_Size+1)]->GetCurrentType() == TWO_LAYER_COOKIE_OBJECT)  {
                        MakeDisappearWithObject( m_Stage_Object[i]->GetInformationNeibor()[j]%(m_Size+1) );
                    }
                }
            }
        }
    }
}

void StageObject::MakeDisappearWithTriangleFlower( int current_pos ) {
    m_Stage_Object[current_pos]->DisAppear();
    m_Stage_Object[current_pos]->SetAppearBool( false );
    // // cout << "TRIANGLE_FLOWER\n";
    for ( int i = 0 ; i < 6 ; ++i )
    {
        if (m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1) != -1)
            MakeDisappearWithObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1)  );
    }
    if (m_Stage_Object[current_pos]->GetInformationNeibor()[0]%(m_Size+1) != -1 && m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[0]%(m_Size+1) ] ->GetInformationNeibor()[5]%(m_Size+1) != -1)
        MakeDisappearWithObject( m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[0]%(m_Size+1) ] ->GetInformationNeibor()[5]%(m_Size+1) );

    if (m_Stage_Object[current_pos]->GetInformationNeibor()[2]%(m_Size+1) != -1 && m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[2]%(m_Size+1) ] ->GetInformationNeibor()[1]%(m_Size+1) != -1)
        MakeDisappearWithObject( m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[2]%(m_Size+1) ] ->GetInformationNeibor()[1]%(m_Size+1) );

    if (m_Stage_Object[current_pos]->GetInformationNeibor()[4]%(m_Size+1) != -1 && m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[4]%(m_Size+1) ] ->GetInformationNeibor()[3]%(m_Size+1) != -1)
        MakeDisappearWithObject( m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[4]%(m_Size+1) ] ->GetInformationNeibor()[3]%(m_Size+1) );

}

void StageObject::MakeDisappearWithFlower( int current_pos ) {
    m_Stage_Object[current_pos]->DisAppear();
    m_Stage_Object[current_pos]->SetAppearBool( false );
    // // cout << "FLOWER\n";
    for ( int i = 0 ; i < 6 ; ++i )
    {
        if (m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1) != -1){
            MakeDisappearWithObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1) );
        }

    }
    if (m_Stage_Object[current_pos]->GetInformationNeibor()[0]%(m_Size+1) != -1 && m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[0]%(m_Size+1) ] ->GetInformationNeibor()[5]%(m_Size+1) != -1){
        MakeDisappearWithObject( m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[0]%(m_Size+1) ] ->GetInformationNeibor()[5]%(m_Size+1)  );
    }
    if (m_Stage_Object[current_pos]->GetInformationNeibor()[0]%(m_Size+1) != -1 && m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[0]%(m_Size+1) ] ->GetInformationNeibor()[1]%(m_Size+1) != -1){
        MakeDisappearWithObject( m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[0]%(m_Size+1) ] ->GetInformationNeibor()[1]%(m_Size+1) );
    }
    if (m_Stage_Object[current_pos]->GetInformationNeibor()[3]%(m_Size+1) != -1 && m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[3]%(m_Size+1) ] ->GetInformationNeibor()[2]%(m_Size+1) != -1){
        MakeDisappearWithObject( m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[3]%(m_Size+1) ] ->GetInformationNeibor()[2]%(m_Size+1)  );
    }
    if (m_Stage_Object[current_pos]->GetInformationNeibor()[3]%(m_Size+1) != -1 && m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[3]%(m_Size+1) ] ->GetInformationNeibor()[4]%(m_Size+1) != -1){
        MakeDisappearWithObject( m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[3]%(m_Size+1) ] ->GetInformationNeibor()[4]%(m_Size+1) );
    }
    if (m_Stage_Object[current_pos]->GetInformationNeibor()[1]%(m_Size+1) != -1 && m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[1]%(m_Size+1) ] ->GetInformationNeibor()[2]%(m_Size+1) != -1){
        MakeDisappearWithObject( m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[1]%(m_Size+1) ] ->GetInformationNeibor()[2]%(m_Size+1) );
    }
    if (m_Stage_Object[current_pos]->GetInformationNeibor()[5]%(m_Size+1) != -1 && m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[5]%(m_Size+1) ] ->GetInformationNeibor()[4]%(m_Size+1) != -1){
        MakeDisappearWithObject( m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[5]%(m_Size+1) ] ->GetInformationNeibor()[4]%(m_Size+1) );
    }
}

void StageObject::MakeDisappearWithStarFlower( int current_pos ) {
    m_Stage_Object[current_pos]->DisAppear();
    m_Stage_Object[current_pos]->SetAppearBool( false );
    // // cout << "STAR_FLOWER\n";
    for ( int i = 0 ; i < 6 ; ++i )
    {
        if (m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1) != -1){
            MakeDisappearWithObject( m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1)  );

            if (m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1)] ->GetInformationNeibor()[i]%(m_Size+1) != -1)
                MakeDisappearWithObject( m_Stage_Object[m_Stage_Object[current_pos]->GetInformationNeibor()[i]%(m_Size+1)] ->GetInformationNeibor()[i]%(m_Size+1) );

        }
    }
}
