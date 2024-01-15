Visual studio 2022 c


you need to install this package

NuGet\Install-Package Microsoft.DXSDK.D3DX -Version 9.29.952.8
NuGet\Install-Package directxtk_desktop_2019 -Version 2024.1.1.1

NuGet\Install-Package directxtex_desktop_win10 -Version 2024.1.1.1

NuGet\Install-Package directxtex_uwp -Version 2024.1.1.1

C:\>md clone
C:\>cd clone
git clone https://github.com/microsoft/vcpkg
C:\clone>cd vcpkg
C:\clone\vcpkg>bootstrap-vcpkg.bat
C:\clone\vcpkg>vcpkg install directxtex
C:\clone\vcpkg>vcpkg install directxtex:x64-windows
C:\clone\vcpkg>vcpkg install directxtex:x64-uwp


add speak
add font

*******************************************************
sound engine 5 for now test
looking for something easy
*******************************************************

 
