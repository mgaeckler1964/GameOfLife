/*
		Project:		Game Of Life
		Module:			gameOfLife.cpp
		Description:	A Game Of Life Simulation
		Author:			Martin Gäckler
		Address:		Hofmannsthalweg 14, A-4030 Linz
		Web:			https://www.gaeckler.at/

		Copyright:		(c) 2026 Martin Gäckler

		This program is free software: you can redistribute it and/or modify
		it under the terms of the GNU General Public License as published by
		the Free Software Foundation, version 3.

		You should have received a copy of the GNU General Public License
		along with this program. If not, see <http://www.gnu.org/licenses/>.

		THIS SOFTWARE IS PROVIDED BY Martin Gäckler, Linz, Austria ``AS IS''
		AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
		TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
		PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR
		CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
		SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
		LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
		USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
		ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
		OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
		OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
		SUCH DAMAGE.
*/

// --------------------------------------------------------------------- //
// ----- switches ------------------------------------------------------ //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- includes ------------------------------------------------------ //
// --------------------------------------------------------------------- //

#include <gak/fmtNumber.h>

#include <WINLIB/WINAPP.H>
#include <winlib/POPUP.H>
#include <WINLIB/colors.h>

#include "gameOfLife_rc.h"
#include "gameOfLife.gui.h"

// --------------------------------------------------------------------- //
// ----- imported datas ------------------------------------------------ //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- module switches ----------------------------------------------- //
// --------------------------------------------------------------------- //

#ifdef __BORLANDC__
#	pragma option -RT-
#	pragma option -b
#	pragma option -a4
#	pragma option -pc
#endif

using namespace winlib;

// --------------------------------------------------------------------- //
// ----- constants ----------------------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- macros -------------------------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- type definitions ---------------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- class definitions --------------------------------------------- //
// --------------------------------------------------------------------- //

class LifeGameWindow : public winlibGUI::LifeGameFORM_form
{
	gak::Matrix<bool>	m_area;
	double				m_cellWidth, m_cellHeight;
	int					m_generations;

	void setLifeSize( const winlib::Size &clientSize )
	{
		unsigned areaWidth = WidthEDIT->getText().getValueN<unsigned>();
		unsigned areaHeight = HeightEDIT->getText().getValueN<unsigned>();

		unsigned oldRows = unsigned(m_area.getNumRows());
		unsigned oldCols = unsigned(m_area.getNumCols());
		if( areaWidth && areaHeight )
		{
			m_area.setNumCols( areaWidth );
			m_area.setNumRows( areaHeight );
			m_cellWidth = double(clientSize.width)/areaWidth;
			m_cellHeight = double(clientSize.height)/areaHeight;
		}
		if( oldRows != areaHeight || oldCols != areaWidth )
		{
			for( int col=0; col<m_area.getNumCols(); ++col )
				for( int row=0; row<m_area.getNumRows(); ++row )
					m_area[col][row] = randomNumber( 100 ) < 30;
		}
	}
	// window messages
	ProcessStatus handleCreate() override;
	ProcessStatus handleResize( const Size &newSize ) override;
	ProcessStatus handleErase( Device &hDC ) override;
	ProcessStatus handleRepaintFrame( const FrameChild *frame ) override;
	SuccessCode handleClose() override;

	// mouse messages
	ProcessStatus handleLeftButton( LeftButton leftButton, ModifierFlags modifier, const Point &position ) override;

	// windows controls
	ProcessStatus handleEditChange( int control ) override;
	ProcessStatus handleButtonClick( int control ) override;

	// other
	void handleTimer() override;

	public:
	LifeGameWindow();
};

class WindowsApplication : public winlibGUI::GuiApplication
{
	bool startApplication( HINSTANCE /*hInstance*/, const char * /*cmdLine*/ ) override
	{
		doEnableLogEx(gakLogging::llInfo);
		doDisableLog();
		setApplication("GameOfLife");
		setCompany("gak");
		return 0;
	}
	CallbackWindow *createMainWindow( const char * /*cmdLine*/, ShowWindowMode /*nCmdShow*/ ) override
	{
		std::unique_ptr<LifeGameWindow>	mainWindow( new LifeGameWindow );
		if( mainWindow->create( nullptr ) == scERROR )
		{
			throw gak::LibraryException( "Could not create window!" );
		}

		mainWindow->focus();
		return mainWindow.release();
	}
	void deleteMainWindow( BasicWindow  *mainWindow ) override
	{
		delete mainWindow;
	}

	public:
	WindowsApplication() : GuiApplication( IDI_GAME_OF_LIFE ) {}
};

// --------------------------------------------------------------------- //
// ----- exported datas ------------------------------------------------ //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- module static data -------------------------------------------- //
// --------------------------------------------------------------------- //

static WindowsApplication	app;

// --------------------------------------------------------------------- //
// ----- class static data --------------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- prototypes ---------------------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- module functions ---------------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- class inlines ------------------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- class constructors/destructors -------------------------------- //
// --------------------------------------------------------------------- //

LifeGameWindow::LifeGameWindow() : LifeGameFORM_form( nullptr ), m_cellWidth(0), m_cellHeight(0)
{
}

// --------------------------------------------------------------------- //
// ----- class static functions ---------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- class privates ------------------------------------------------ //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- class protected ----------------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- class virtuals ------------------------------------------------ //
// --------------------------------------------------------------------- //

// window messages

ProcessStatus LifeGameWindow::handleCreate()
{
	LifeArea->notifyParent();
	return psPROCESSED;
}

SuccessCode LifeGameWindow::handleClose()
{
	return OverlappedWindow::handleClose();
}

ProcessStatus LifeGameWindow::handleResize( const Size &newSize )
{
	ProcessStatus	result = OverlappedWindow::handleResize( newSize );
	if( isControlsOK() )
	{
		setLifeSize(LifeArea->getClientSize());
	}
	return result;

}

ProcessStatus LifeGameWindow::handleErase( Device & )
{
	return psPROCESSED;
}

ProcessStatus LifeGameWindow::handleRepaintFrame( const FrameChild *frame )
{
	if( frame == LifeArea )
	{
		gak::StopWatch		sw( true );

		winlib::DrawDevice	winDD( frame );

		const Brush			life = winlib::Brush().create(colors::RED );
		const Brush			green = winlib::Brush().create(colors::GREEN );

#define FAST 1

#if FAST
		MemoryDevice		memDD( winDD, frame->getClientSize() );
		Device				&dd = memDD;
#else
		Device				&dd = winDD;
#endif

		for( size_t col=0; col<m_area.getNumCols(); ++col )
		{
			for( size_t row=0; row<m_area.getNumRows(); ++row )
			{
				const bool	living = m_area[col][row];
				const Brush	&color = (living ? life : green);
				const int	left = gak::math::round<int>(col * m_cellWidth);
				const int	top = gak::math::round<int>(row * m_cellHeight);
				const int	right = gak::math::round<int>((col+1) * m_cellWidth);
				const int	bottom = gak::math::round<int>((row+1) * m_cellHeight);
				dd.fillRectangle( RectBorder(left, top, right, bottom), color );
			}
		}

#if FAST
		memDD.drawToWindow();
#endif
		sw.stop();
		Time2LABEL->setText( gak::NumberBuffer().addNumber( sw.getMillis() ).addCP( "ms" ).c_str() );
	}
	return psPROCESSED;
}

ProcessStatus LifeGameWindow::handleLeftButton( LeftButton leftButton, ModifierFlags , const Point &mouse )
{
	if( lbDOWN==leftButton )
	{
		Point	area = mouse;
	
		mapMousePosition( LifeArea, &area );
		int col = int( area.x / m_cellWidth );
		int row = int( area.y / m_cellHeight );
		if( col >= 0 && row >= 0 && col < m_area.getNumCols() && row<m_area.getNumRows() )
		{
			bool &life = m_area[col][row];
			life = !life;
			invalidateWindow();
		}
	}
	return psPROCESSED;
}


// windows controls

ProcessStatus LifeGameWindow::handleEditChange( int control )
{
	if( control == winlibGUI::WidthEDIT_id || control == winlibGUI::HeightEDIT_id )
	{
		setLifeSize(LifeArea->getClientSize());
		invalidateWindow();
	}
	return OverlappedWindow::handleEditChange( control );
}

ProcessStatus LifeGameWindow::handleButtonClick( int buttonID )
{
	if( buttonID == winlibGUI::StartBUTTON_id )
	{
		m_generations = 1;
		setTimer( 100 );
		return psPROCESSED;
	}
	else if( buttonID == winlibGUI::StopBUTTON_id)
	{
		removeTimer();
		return psPROCESSED;
	}

	return OverlappedWindow::handleButtonClick( buttonID );
}

// other

void LifeGameWindow::handleTimer()
{
	gak::StopWatch		sw( true );
	bool				oneCell = false;
	bool				noChange = true;

	gak::Matrix<bool>	currentState = m_area;
	for( int col=0; col<currentState.getNumCols(); ++col )
	{
		for( int row=0; row<currentState.getNumRows(); ++row )
		{
			int numNeighbors = 0;

			// offsets
			for( int colO = -1; colO <= 1; ++ colO )
			{
				for( int rowO = -1; rowO <= 1; ++rowO )
				{
					if( colO || rowO )	// not both offsets must be zero
					{
						// neighbors
						int colN = col+colO;
						int rowN = row+rowO;
						if( colN >= 0 && rowN >= 0 && colN < currentState.getNumCols() && rowN < currentState.getNumRows() && currentState[colN][rowN] )
							numNeighbors++;
					}
				}
			}
			const bool oldState = currentState[col][row];
			bool newState = oldState;
			if( oldState && numNeighbors < 2 || numNeighbors > 3 )
				newState = false;	// cell is dying
			else if( !oldState && numNeighbors == 3 )
				newState = true;	// cell born
			oneCell = oneCell || newState;
			if( oldState != newState )
			{
				m_area[col][row] = newState;
				noChange = false;
			}
		}
	}
	sw.stop();
	TimeLABEL->setText( gak::NumberBuffer().addNumber( sw.getMillis() ).addCP( "ms" ).c_str() );
	CountLABEL->setText( gak::NumberBuffer().addNumber(++m_generations).c_str() );
	LifeArea->invalidateWindow( false );

	if( !oneCell )
	{
		removeTimer();
		messageBox("All Cells died", "End Of Life" ); 
	}
	else if( noChange )
	{
		removeTimer();
		messageBox("Infinite Life", "No Progress" ); 
	}
}

// --------------------------------------------------------------------- //
// ----- class publics ------------------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- entry points -------------------------------------------------- //
// --------------------------------------------------------------------- //

#ifdef __BORLANDC__
#	pragma option -RT.
#	pragma option -b.
#	pragma option -a.
#	pragma option -p.
#endif

