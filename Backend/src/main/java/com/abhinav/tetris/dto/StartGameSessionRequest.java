package com.abhinav.tetris.dto;

import jakarta.validation.constraints.NotBlank;

public record StartGameSessionRequest(
        @NotBlank(message = "id should not be blank")
        Long id
) { }
