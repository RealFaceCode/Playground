mkdir buildpacked
cd buildpacked

mkdir binary
mkdir assets
mkdir data
cd ..

for /f "delims=" %%F in ('dir /b /s "./Playground.exe" 2^>nul') do set MyVariable=%%F

copy /b %MyVariable% .\buildpacked\binary
robocopy .\assets .\buildpacked\assets /s /e
robocopy .\data .\buildpacked\data /s /e

pause