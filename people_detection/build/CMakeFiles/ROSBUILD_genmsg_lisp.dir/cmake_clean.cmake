FILE(REMOVE_RECURSE
  "../msg_gen"
  "../msg_gen"
  "../src/people_detection/msg"
  "CMakeFiles/ROSBUILD_genmsg_lisp"
  "../msg_gen/lisp/person_cluster.lisp"
  "../msg_gen/lisp/_package.lisp"
  "../msg_gen/lisp/_package_person_cluster.lisp"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_lisp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
