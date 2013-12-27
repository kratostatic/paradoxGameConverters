copy "Data Files\blocked_nations.txt" "release\blocked_nations.txt"
copy "Data Files\configuration.txt" "release\configuration.txt"
copy "Data Files\country_mappings.txt" "release\country_mappings.txt"
copy "Data Files\culture_mappings.txt" "release\culture_mappings.txt"
copy "Data Files\religion_mappings.txt" "release\religion_mappings.txt"
copy "Data Files\province_mappings.txt" "release\province_mappings.txt"
copy "Data Files\readme.txt" "release\readme.txt"
xcopy /E /Y /Q /I "Converter Mod" "Release"

hg log --template "Change:\t\t{rev}: {node}\nAuthor:\t\t{author}\nDescription:\t{desc}\nDate:\t\t{date|isodate}\nBranch:\t\t{branch}\n***\n" > Release/log.txt
(for /f "delims=" %%i in (release/log.txt) do @echo %%i)>release/changelog.txt
del release\log.txt
