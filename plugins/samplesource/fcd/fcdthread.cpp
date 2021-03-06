///////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2012 maintech GmbH, Otto-Hahn-Str. 15, 97204 Hoechberg, Germany //
// written by Christian Daniel                                                   //
//                                                                               //
// This program is free software; you can redistribute it and/or modify          //
// it under the terms of the GNU General Public License as published by          //
// the Free Software Foundation as version 3 of the License, or                  //
//                                                                               //
// This program is distributed in the hope that it will be useful,               //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// GNU General Public License V3 for more details.                               //
//                                                                               //
// You should have received a copy of the GNU General Public License             //
// along with this program. If not, see <http://www.gnu.org/licenses/>.          //
///////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <errno.h>
#include "fcdthread.h"
#include "dsp/samplefifo.h"

FCDThread::FCDThread(SampleFifo* sampleFifo, QObject* parent) :
	QThread(parent),
	fcd_handle(NULL),
	m_running(false),
	m_convertBuffer(BLOCKSIZE),
	m_sampleFifo(sampleFifo)
{
	start();
}

FCDThread::~FCDThread()
{
}

void FCDThread::stopWork()
{
	m_running = false;
	wait();
}

void FCDThread::run()
{
	if ( !OpenSource("hw:CARD=V20") )
                return;
	// TODO: fallback to original fcd

	m_running = true;
	while(m_running) {
		if ( work(BLOCKSIZE) < 0)
			break;
	}
	CloseSource();
}

