#Under construction
# from mpl_toolkits.basemap import Basemap
# from mpl_toolkits import mplot3d

# import plotly
import numpy as np
import plotly.graph_objects as go 

def spheres(size, clr): 
    
    # Set up 100 points. First, do angles
    theta = np.linspace(0,2*np.pi,100)
    phi = np.linspace(0,np.pi,100)
    
    # Set up coordinates for points on the sphere
    x0 = size * np.outer(np.cos(theta),np.sin(phi))
    y0 = size * np.outer(np.sin(theta),np.sin(phi))
    z0 = size * np.outer(np.ones(100),np.cos(phi))
    
    # Set up trace
    trace= go.Surface(x=x0, y=y0, z=z0, colorscale=[[0,clr], [1,clr]])
    trace.update(showscale=False)

    return trace

spheres(6787, '#b20000')
# marstrace = spheres(6787, '#b20000')

# layout=go.Layout(title = 'Solar System', showlegend=False, margin=dict(l=0, r=0, t=0, b=0),
#                   #paper_bgcolor = 'black',
#                   scene = dict(xaxis=dict(title='Distance from the Sun', 
#                                           titlefont_color='black', 
#                                           range=[-7000,7000], 
#                                           backgroundcolor='black',
#                                           color='black',
#                                           gridcolor='black'),
#                                yaxis=dict(title='Distance from the Sun',
#                                           titlefont_color='black',
#                                           range=[-7000,7000],
#                                           backgroundcolor='black',
#                                           color='black',
#                                           gridcolor='black'
#                                           ),
#                                zaxis=dict(title='', 
#                                           range=[-7000,7000],
#                                           backgroundcolor='black',
#                                           color='white', 
#                                           gridcolor='black'
#                                          )
#                                ))

# fig = go.Figure(data = marstrace,
#                 layout = layout)

# fig.show()
# fig.write_html("Solar_system.html")