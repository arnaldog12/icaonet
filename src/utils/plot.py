import numpy as np
import matplotlib.pyplot as plt

def requirements_count(list_mrk_files, fig_size=(6, 6), fig_title='', fig_color=None):
    req_names = list_mrk_files[0].photo_reqs.get_descriptions()
    n_reqs = len(req_names)

    list_req_values = np.array([mrk_file.photo_reqs.is_com() for mrk_file in list_mrk_files])
    list_req_values = list_req_values.sum(axis=0)

    fig, ax = plt.subplots()
    fig.set_size_inches(*fig_size)
    ax.barh(range(n_reqs), list_req_values, color=fig_color)
    ax.invert_yaxis()
    ax.set_yticks(range(n_reqs))
    ax.set_yticklabels(req_names)
    plt.title(fig_title)
    plt.show()
    return list_req_values
