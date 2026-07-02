package com.abhinav.tetris.dto;

import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.Size;

public record LoginRequest(
        @NotBlank(message = "Name must not be blank")
        String name,

        @NotBlank(message = "Password must not be blank")
        String password
) {
}
