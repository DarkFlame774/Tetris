package com.abhinav.tetris.dto;

import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.Size;

public record StartGameSessionRequest(
        @NotBlank
        @Size(min = 1, max = 15)
        String name
) { }
