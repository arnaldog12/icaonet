import numpy as np
import matplotlib.pyplot as plt
import itertools

def image_batch(batch, y_true, y_pred=None, labels=None, n_cols=10, figsize=(16,5)):
    plt.figure(figsize=figsize)
    
    y_pred = y_true if y_pred is None else y_pred
    labels = y_true if labels is None else labels
    n_rows = batch.shape[0] // n_cols + 1
    for img, true, pred, sub in zip(batch, y_true, y_pred, range(1, len(batch)+1)):
        plt.subplot(n_rows, n_cols, sub)
        plt.imshow(img.astype(np.uint8))
        
        plt.title("{}".format(labels[pred]), color = 'green' if true == pred else 'red')
        plt.axis('off')
    plt.tight_layout()

def plot_keras_hist(history, figsize=(12, 4), loss_train_key='loss', loss_val_key='val_loss', metric_train_key='acc', metric_val_key='val_acc'):
    loss_train = history.get(loss_train_key, [])
    loss_valid = history.get(loss_val_key, [])
    metric_train = history.get(metric_train_key, [])
    metric_valid = history.get(metric_val_key, [])

    plt.figure(figsize=figsize)
    plt.subplot(1, 2, 1)
    plt.plot(loss_train, label='train')
    plt.plot(loss_valid, label='val')
    plt.ylim(0)
    plt.legend()

    if len(metric_train) > 0 or len(metric_valid) > 0:
        plt.subplot(1, 2, 2)
        plt.plot(metric_train, label='train')
        plt.plot(metric_valid, label='val')
        plt.ylim(top=1)
        plt.legend()

def plot_confusion_matrix(cm, target_names, title='Confusion matrix', cmap=None, normalize=False, figsize=(8, 6), fontsize=16):
    """
    given a sklearn confusion matrix (cm), make a nice plot

    Arguments
    ---------
    cm:           confusion matrix from sklearn.metrics.confusion_matrix
    target_names: given classification classes such as [0, 1, 2]
                  the class names, for example: ['high', 'medium', 'low']
    title:        the text to display at the top of the matrix
    cmap:         the gradient of the values displayed from matplotlib.pyplot.cm
                  see http://matplotlib.org/examples/color/colormaps_reference.html
                  plt.get_cmap('jet') or plt.cm.Blues
    normalize:    If False, plot the raw numbers
                  If True, plot the proportions
    Usage
    -----
    plot_confusion_matrix(cm           = cm,                  # confusion matrix created by
                                                              # sklearn.metrics.confusion_matrix
                          normalize    = True,                # show proportions
                          target_names = y_labels_vals,       # list of names of the classes
                          title        = best_estimator_name) # title of graph
    Citiation
    ---------
    http://scikit-learn.org/stable/auto_examples/model_selection/plot_confusion_matrix.html
    """

    accuracy = np.trace(cm) / float(np.sum(cm))
    misclass = 1 - accuracy

    if cmap is None:
        cmap = plt.get_cmap('Blues')

    plt.title('{} ({:.2f}%)'.format(title, accuracy * 100))

    if target_names is not None:
        tick_marks = np.arange(len(target_names))
        plt.xticks(tick_marks, target_names)
        plt.yticks(tick_marks, target_names)

    if normalize:
        row_sum = cm.sum(axis=1, keepdims=True, dtype=np.float32)
        row_sum[row_sum == 0] = np.inf
        norm = cm.astype('float') / row_sum
        
    plt.imshow(norm if normalize else cm, interpolation='nearest', cmap=cmap)

    thresh = norm.max() / 1.5 if normalize else cm.max() / 1.5
    for i, j in itertools.product(range(cm.shape[0]), range(cm.shape[1])):
        plt.text(j, i, "{:,}".format(cm[i, j]),
                     horizontalalignment="center", 
                     fontsize=fontsize,
                     color="white" if cm[i, j] > thresh and norm[i, j] > thresh else "black")

    plt.tight_layout()
    plt.ylabel('True label')
