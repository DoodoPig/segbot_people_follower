; Auto-generated. Do not edit!


(cl:in-package people_detection-msg)


;//! \htmlinclude person_cluster.msg.html

(cl:defclass <person_cluster> (roslisp-msg-protocol:ros-message)
  ((depth
    :reader depth
    :initarg :depth
    :type cl:float
    :initform 0.0)
   (x
    :reader x
    :initarg :x
    :type cl:float
    :initform 0.0)
   (indicator
    :reader indicator
    :initarg :indicator
    :type cl:fixnum
    :initform 0))
)

(cl:defclass person_cluster (<person_cluster>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <person_cluster>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'person_cluster)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name people_detection-msg:<person_cluster> is deprecated: use people_detection-msg:person_cluster instead.")))

(cl:ensure-generic-function 'depth-val :lambda-list '(m))
(cl:defmethod depth-val ((m <person_cluster>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader people_detection-msg:depth-val is deprecated.  Use people_detection-msg:depth instead.")
  (depth m))

(cl:ensure-generic-function 'x-val :lambda-list '(m))
(cl:defmethod x-val ((m <person_cluster>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader people_detection-msg:x-val is deprecated.  Use people_detection-msg:x instead.")
  (x m))

(cl:ensure-generic-function 'indicator-val :lambda-list '(m))
(cl:defmethod indicator-val ((m <person_cluster>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader people_detection-msg:indicator-val is deprecated.  Use people_detection-msg:indicator instead.")
  (indicator m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <person_cluster>) ostream)
  "Serializes a message object of type '<person_cluster>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'depth))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'indicator)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <person_cluster>) istream)
  "Deserializes a message object of type '<person_cluster>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'depth) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'x) (roslisp-utils:decode-double-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'indicator)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<person_cluster>)))
  "Returns string type for a message object of type '<person_cluster>"
  "people_detection/person_cluster")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'person_cluster)))
  "Returns string type for a message object of type 'person_cluster"
  "people_detection/person_cluster")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<person_cluster>)))
  "Returns md5sum for a message object of type '<person_cluster>"
  "7ebfa6761596b01a46ac5d45e08fa708")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'person_cluster)))
  "Returns md5sum for a message object of type 'person_cluster"
  "7ebfa6761596b01a46ac5d45e08fa708")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<person_cluster>)))
  "Returns full string definition for message of type '<person_cluster>"
  (cl:format cl:nil "float64 depth~%float64 x~%uint8 indicator~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'person_cluster)))
  "Returns full string definition for message of type 'person_cluster"
  (cl:format cl:nil "float64 depth~%float64 x~%uint8 indicator~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <person_cluster>))
  (cl:+ 0
     8
     8
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <person_cluster>))
  "Converts a ROS message object to a list"
  (cl:list 'person_cluster
    (cl:cons ':depth (depth msg))
    (cl:cons ':x (x msg))
    (cl:cons ':indicator (indicator msg))
))
