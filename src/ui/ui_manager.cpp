#include <algorithm>

#include "ui/ui_manager.hpp"

#include "ui/ui.hpp"


namespace hin {

    void UIManager::Update( ) {
        for( auto ui : this->__uis ) {
            ui->Update( );
        }
    }


    void UIManager::Render( SDL_Renderer *renderer ) {
        for( auto ui : this->__uis ) {
            ui->Render( renderer );
        }
    }


    void UIManager::HandleEvent( SDL_Event &event ) {
        for( auto ui : this->__uis ) {
            ui->HandleEvent( event );
        }
    }


    void UIManager::AddUI( UI *ui ) {
        this->__uis.push_back( ui );
    }


    void UIManager::RemoveUI( UI *ui ) {
        this->__uis.erase( std::remove( __uis.begin( ), __uis.end( ), ui ), __uis.end( ) );
    }

}

