library("rgl")
library("png")
library(plotly)

# # spheres3d(0,0,0,lit=FALSE,color="white")
# # spheres3d(0,0,0,radius=1.01,lit=FALSE,color="black",front="lines")


# # n <- 50
# # theta <- runif(n,0,2*pi)
# # u <- runif(n,-1,1)
# # x <- sqrt(1-u^2)*cos(theta)
# # y <- sqrt(1-u^2)*sin(theta)
# # z <- u



# read a sample file (R logo)
img <- readPNG("src\\plotOrbits\\mars_surface.png")
# img <- as.raster(img[,,1:3])

# if your R supports it, we'll plot it
if (exists("rasterImage")) { # can plot only in R 2.11.0 and higher
    plot(1:2, type='n')
    rasterImage(img,  1, 2, 2, 1, interpolate=FALSE)
}

img <- as.raster(img)
clr <- '#b20000'
Radius = 6787
phi <- seq(0, pi, length = 200)
theta <- seq(0, 2*pi, length = 200)
x = Radius*outer(sin(phi),cos(theta))
y = Radius*outer(sin(phi),sin(theta))
z = Radius * (matrix(1, 200, 200)*cos(phi))
# print(sqrt(x**2 + y**2 + z**2))
surf <- plot_ly(x = ~x, y = ~y, z = ~z, colorscale = ~list(c(0, img[333,549]), c(1, img[500,1000])), showscale = TRUE) %>% add_surface()



