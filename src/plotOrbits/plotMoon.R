

library(rgdal)


library(raster)
library(rayshader)

moon <- raster("src/plotOrbits/moon.png")
moon_texture <- create_texture(moon, centercolor = "white", lightcolor = "white", shadowcolor = "gray", leftcolor = "black", rightcolor = "black")

# Convert the texture to a grayscale heightmap
moon_heightmap <- texture_image(moon_texture, grayscale = TRUE)

# Create a 3D plot of the moon
plot_3d(moon_heightmap, texture = moon_texture, zoom = 0.5, phi = 45, theta = 45, windowsize = c(800, 600))
# sphere_df <- sphere_shade(texture = moon_texture, 
#                            lambert = FALSE, 
#                            specular = 0, 
#                            phi_resolution = 100, 
#                            theta_resolution = 100)


# plot_map(sphere_df, 
#          windowsize = c(800, 600), 
#          zoom = 0.8, 
#          scale = 1000, 
#          theta = -45, 
#          phi = 20, 
#          background = "#000000")


# print(plot_map)