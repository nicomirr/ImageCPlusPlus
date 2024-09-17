#pragma once

struct CursorOptions
{
	public: 

		CursorOptions();
		virtual ~CursorOptions() = 0;

        static void SetCursorPosition(int x, int y);
       

};

