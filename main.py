import numpy as np
import tensorflow as tf
import math


def nme_metric_ops(labels, landmarks):
    """
    Arguments:
        labels, landmarks: a float tensors with shape [batch_size, num_landmarks, 2].
    Returns:
        two ops like in tf.metrics API.
    """
    norms = tf.norm(labels - landmarks, axis=2)  # shape [batch_size, num_landmarks]
    mean_norm = tf.reduce_mean(norms, axis=1)  # shape [batch_size]
    eye_distance = tf.norm(labels[:, 0, :] - labels[:, 1, :], axis=1)  # shape [batch_size]

    values = mean_norm/tf.maximum(eye_distance, 1.0)
    mean = tf.reduce_mean(values)
    return mean


def nme_metric_ops_2(labels, landmarks):
    """
    Arguments:
        labels, landmarks: a float tensors with shape [batch_size, num_landmarks, 2].
    Returns:
        two ops like in tf.metrics API.
    """
    norms = tf.norm(labels - landmarks, axis=1)  # shape [batch_size, num_landmarks]
    mean_norm = tf.reduce_mean(norms, axis=0)  # shape [batch_size]
    eye_distance = tf.norm(labels[:, 0:2] - labels[:, 2:])  # shape [batch_size]

    values = mean_norm/tf.maximum(eye_distance, 1.0)
    mean = tf.reduce_mean(values)
    return mean


BATCH_SIZE = 100
y_true = np.random.rand(BATCH_SIZE, 2, 2)
y_pred = np.random.rand(BATCH_SIZE, 2, 2)

y_true_tf = tf.Variable(y_true, dtype=tf.float32)
y_pred_tf = tf.Variable(y_pred, dtype=tf.float32)

y_true_tf2 = tf.Variable(y_true.reshape(BATCH_SIZE, 4), dtype=tf.float32)
y_pred_tf2 = tf.Variable(y_pred.reshape(BATCH_SIZE, 4), dtype=tf.float32)

with tf.Session() as sess:
    init = tf.global_variables_initializer()
    init_local = tf.local_variables_initializer()
    sess.run([init, init_local])

    result = nme_metric_ops(y_true_tf, y_pred_tf)
    print(result.eval())

    result = nme_metric_ops_2(y_true_tf2, y_pred_tf2)
    print(result.eval())
