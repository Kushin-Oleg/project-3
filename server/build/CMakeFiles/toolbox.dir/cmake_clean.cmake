file(REMOVE_RECURSE
  "libtoolbox.a"
  "libtoolbox.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/toolbox.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
