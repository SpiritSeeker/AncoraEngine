#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <thread>

#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <unordered_set>
#include <unordered_map>

// Networking
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>

#include "Ancora/Core/Log.h"

#ifdef AE_PLATFORM_WINDOWS
	#include <Windows.h>
#endif
