import numpy as np
import matplotlib.pyplot as plt

def requirements_count(list_mrk_files, fig_size=(6, 6), fig_title='', fig_color=None):
    req_names = [req.description for req in list_mrk_files[0].photo_reqs]
    n_reqs = len(req_names)

    list_req_values = []
    for mrk_file in list_mrk_files:
        list_req_values.append([req.is_non_compliant() for req in mrk_file.photo_reqs])

    req_counts = np.array(list_req_values).sum(axis=0)

    fig, ax = plt.subplots()
    fig.set_size_inches(*fig_size)
    ax.barh(range(n_reqs), req_counts, color=fig_color)
    ax.invert_yaxis()
    ax.set_yticks(range(n_reqs))
    ax.set_yticklabels(req_names)
    plt.title(fig_title)
    plt.show()
    return req_counts
