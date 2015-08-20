
(cl:in-package :asdf)

(defsystem "people_detection-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "person_cluster" :depends-on ("_package_person_cluster"))
    (:file "_package_person_cluster" :depends-on ("_package"))
  ))