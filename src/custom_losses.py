import math

import tensorflow as tf


def wing_loss(landmarks, labels, w=100.0, epsilon=2.0):
    """
    Arguments:
        landmarks, labels: float tensors with shape [batch_size, 4].
        w, epsilon: a float numbers.
    Returns:
        a float tensor with shape [].

    Based on: https://github.com/TropComplique/wing-loss/blob/master/loss.py
    """
    with tf.name_scope('wing_loss'):
        x = landmarks - labels
        c = w * (1.0 - math.log(1.0 + w/epsilon))
        absolute_x = tf.abs(x)
        losses = tf.where(
            tf.greater(w, absolute_x),
            w * tf.log(1.0 + absolute_x/epsilon),
            absolute_x - c
        )
        loss = tf.reduce_mean(tf.reduce_sum(losses, axis=-1), axis=0)
        return loss
