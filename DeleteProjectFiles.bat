echo Deleting all project files

@echo off

if exist "./build" (
    echo Deleting directory: "./build"
    rd /s /q "./build"
)

set "extensions=.sln .vcxproj .vcxproj.filters .vcxproj.users"

for /D %%d in (*) do (
    echo Processing directory: %%d
    cd "%%d"
    for %%e in (%extensions%) do (
         if exist "*%%e" (
            del /q *%%e
         )
    )
    cd ..
)

del "./*.sln"

echo Complete!
@echo on

PAUSE