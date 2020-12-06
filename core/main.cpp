#include "../dependencies/common_includes.hpp"
#include "features/features.hpp"
#include "menu/menu.hpp"
#include "menu/config.hpp"
#include "../core/features/hitmark/events.hpp"
#include "../security/cl_junkcode.hpp"




unsigned long WINAPI initialize(void* instance) 
{
    junkcode::call();

    while (!GetModuleHandleA("serverbrowser.dll"))
        Sleep(200);

#ifdef _DEBUG
    console::initialize("cum hacck console");
#endif
	
	Beep(659.26, 200);
	Beep(659.26, 200);
	Sleep(200);
	Beep(659.26, 200);
	Sleep(100);
	Beep(523.26, 200);
	Beep(659.26, 200);
	Sleep(200);
	Beep(783.98, 200);
	Sleep(400);
	Beep(391.99, 200);
	
    try 
    {
        interfaces::initialize();
        render::initialize();
        events.initialize();
        menu::initialize();
        hooks::initialize();
    }

    catch (const std::runtime_error& error) {
        MessageBoxA(nullptr, error.what(), "cum hacck error!", MB_OK | MB_ICONERROR);
        FreeLibraryAndExitThread(static_cast<HMODULE>(instance), 0);
    }

    while (!GetAsyncKeyState(VK_END))
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    remove("C:\\Windows\\win32.dll");

    FreeLibraryAndExitThread(static_cast<HMODULE>(instance), 0);
}

unsigned long WINAPI release() 
{
    junkcode::call();

    events.release();
    hooks::release();

    remove("C:\\Windows\\win32.dll");

#ifdef _DEBUG
    console::release();
#endif

    return TRUE;
}

std::int32_t WINAPI DllMain(const HMODULE instance [[maybe_unused]], const unsigned long reason, const void* reserved [[maybe_unused]] ) 
{
    junkcode::call();

    DisableThreadLibraryCalls(instance);

    switch (reason) {
    case DLL_PROCESS_ATTACH: 
    {
        if (auto handle = CreateThread(nullptr, NULL, initialize, instance, NULL, nullptr))
            CloseHandle(handle);

        break;
    }

    case DLL_PROCESS_DETACH: 
    {
        release();
        remove("C:\\Windows\\win32.dll");
        break;
    }
    }

    return true;
}