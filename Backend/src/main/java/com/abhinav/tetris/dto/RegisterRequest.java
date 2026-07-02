package com.abhinav.tetris.dto;

import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.Size;

public record RegisterRequest(

        @NotBlank(message = "Name must not be blank")
        @Size(max = 10 , message = "Name must no exceed 10 characters")
        String name,

        @NotBlank(message = "Password must not be blank")
        @Size(min = 5, message = "Password must be at least 5 characters long.")
        String password
) { }
