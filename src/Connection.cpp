#include "Connection.h"

Connection::Connection()
{
	isListening = true;
	receive.bind(PORT);
}
