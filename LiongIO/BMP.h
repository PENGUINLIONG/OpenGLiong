#pragma once
#include "LiongIOAPI.h"

using namespace LiongStudio::GL;

_LIO_BEGIN
class _IO_ BMP
{
public:
	/** <summary>Init and read all the metadata.</summary>
	  * <param name='stream'>The stream that we can use to access to the local files.</param>
	  * <param name='width'>Will be filled.</param> 
	  * <param name='height'>Will be filled.</param>
	  * <returns>The length of the data block.</returns>
	  */
	static int InitHeader(ifstream &stream, int &width, int &height);

	/** <summary>Get ready for work.
	  * This function MUST be called before you call the others except 'Automatic'.</summary>
	  * <param name='stream'>The stream that we can use to access to the local files.</param>
	  * <param name='length'>Length of the data.</param>
	  * <returns>Length of data block.</returns>
	  */ 
	static char *ReadData(ifstream &stream, int length);

	/** <summary>Offer a stream and a string and it will finish all the works for you.</summary>
	  * <param name='stream'>The stream that we can use to access to the local files.</param>
	  * <param name='path'>The location of the file that need to be used.</param>
	  * <returns>An opengl texture ID.</returns>
	  */
	static uint Automatic(ifstream &stream, wchar_t *path);
};
_LIO_END
